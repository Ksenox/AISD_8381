var express = require('express');
var app = express();
var mysql = require('mysql');
var path = require('path');
const cw = require('./build/Release/addon');



app.use(express.static(path.join(__dirname, '/front')));
var bodyParser = require("body-parser");
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

//connect to port 3000
app.listen(3000, function () {
    console.log('Serever startd on port 3000!');
});

//conneect to mysql db
var conn = mysql.createConnection({
    host: 'localhost',
    user: 'alpha',
    password: 'tiger007',
    database: 'cw_db',
    multipleStatements: true
});

conn.connect((err) => {
    if (err) throw err;
    console.log("Connected!");
});


app.get('/cw_tree', function (req, res) {
    res.sendFile(__dirname + '/front/cw/cw_tree_screen.html');
});

app.post('/cw_tree', function (req, res) {

    var body = req.body;
    if (body.text_edited) {
        let elems = cw.take_elems();
        let len = elems.split(' ').length - 1;
        let time = cw.take_time();
        let step = cw.take_steps();
        let arr_data = [elems, time, step];

        if (len > 0) {
            let command = "insert into `all_tests` (`itemset`,`time`, `steps`) value (?,?,?);";
            conn.query(command, arr_data, function (err, result) {
                if (err) throw err;
                else res.end(JSON.stringify(result));
            });
        }
        else res.end("_empty_data");

        cw.zeroing();
    }
    if (body.build) {
        let arg1 = body.build.join(' ');
        let arg2 = body.build.length;
        let string_tree = cw.build_tree(arg1, arg2);
        res.end(string_tree);
    }
});


app.get('/cw_table', function (req, res) {
    res.sendFile(__dirname + '/front/cw/cw_table_screen.html');
});

app.post('/cw_table', function (req, res) {
    let body = req.body;
    if (body.obj_out) {
        let command = "select * from `all_tests`";
        if (body.obj_out.from != "") {
            command += " where id>=" + body.obj_out.from;
            if (body.obj_out.to != "")
                command += " and id<=" + body.obj_out.to;
        }
        else if (body.obj_out.to != "") {
            command += " where id<=" + body.obj_out.to;
        }
        conn.query(command, function (err, result) {
            if (err) throw err;
            res.end(JSON.stringify(result));
        });

    }

    if (body.obj_gen) {

        let len = body.obj_gen.len,
            num = body.obj_gen.num,
            flag = body.obj_gen.flag;
        let obj_new_data = {
            "num": num,
            "len": len,
            "time": 0.0,
            "time_2": 0.0,
            "step": 0.0
        };

        let table_name;
        if (flag == "random") { table_name = "average_values"; }
        else if (flag == "average") { table_name = "average_case"; }
        else if (flag == "worst") { table_name = "worst_case"; }

        for (let i = 0; i < num; i++) {
            cw.zeroing();
            let str_elems = cw.data_rand(len);
            if (flag == "average") {
                if (str_elems.split(' ').sort().join(' ') == str_elems) {
                    i--;
                    continue;
                }
            }
            else if (flag == "worst") {
                str_elems = str_elems.split(' ').sort().join(' ');
            }
            let rand_ret = cw.data_test(str_elems, len);
            let elems = cw.take_elems();
            let time = cw.take_time();
            let time_2 = cw.take_time_2();//new
            let step = cw.take_steps();


            let command = "insert into `all_tests` (`itemset`, `time`, `time_2`, `steps`) value (?,?,?,?);";
            conn.query(command, [elems, time, time_2, step], function (err, result) {
                if (err) throw err;
            });
            obj_new_data.time = (obj_new_data.time * (i) + time) / (i + 1);
            obj_new_data.time_2 = (obj_new_data.time_2 * (i) + time_2) / (i + 1);
            obj_new_data.step = (obj_new_data.step * (i) + step) / (i + 1);
        }
        add_in_table_2(table_name, obj_new_data.num, obj_new_data.len, obj_new_data.time, obj_new_data.time_2, obj_new_data.step);

        res.end("done");
    }



});


app.get('/cw_graph', function (req, res) {
    res.sendFile(__dirname + '/front/cw/cw_graph_screen.html');
});


app.post('/cw_graph', function (req, res) {
    let body = req.body;
    if (body.data_to_table) {
        take_data(body.data_to_table, res);
    }
});

app.get('/cw_graph_dop', function (req, res) {
    res.sendFile(__dirname + '/front/cw/cw_graph_dop_screen.html');
});


app.post('/cw_graph_dop', function (req, res) {
    let body = req.body;
    if (body.data_to_table) {
        take_data(body.data_to_table, res);
    }
});

//end

function take_data(table_name, res) {
    let command = "select * from ??";
    conn.query(command, [table_name], function (err, result) {
        if (err) throw err;
        res.end(JSON.stringify(result));
    });
}

function add_in_table_2(table_name, num, len, time, time_2, step) {
    let flag = false;
    let command = "select * from ?? where number_of_leaves=?";
    conn.query(command, [table_name, len], function (err, result) {
        if (err) throw err;
        //console.log(result);
        if (result.length == 0) {
            insert_2([table_name, num, len, time, time_2, step])
        }
        else {
            update(table_name, result, num, len, time, time_2, step)
        }
    });
}





function insert_2(arr_data) {
    let command = "insert into ?? (`number_of_tests`, `number_of_leaves`, `time`, `time_2`, `steps`) value (?,?,?,?,?)";
    conn.query(command, arr_data, function (err, result) {
        if (err) throw err;
    });
}

function update(table_name, result, num, len, time, time_2, step) {
    let command = "update ?? set ??=? where ??=?";
    //number_of_tests update
    conn.query(command, [table_name, "number_of_tests", result[0].number_of_tests + num, "number_of_leaves", len], function (err, result) {
        if (err) throw err;
    });
    command = "update ?? set ??=? where ??=?";
    //time update
    conn.query(command, [table_name, "time", (result[0].time * result[0].number_of_tests + time * num) / (result[0].number_of_tests + num), "number_of_leaves", len], function (err, result) {
        if (err) throw err;
    });

    command = "update ?? set ??=? where ??=?";
    //time_2 update
    conn.query(command, [table_name, "time_2", (result[0].time_2 * result[0].number_of_tests + time_2 * num) / (result[0].number_of_tests + num), "number_of_leaves", len], function (err, result) {
        if (err) throw err;
    });

    command = "update ?? set ??=? where ??=?";
    //steps update
    conn.query(command, [table_name, "steps", (result[0].steps * result[0].number_of_tests + step * num) / (result[0].number_of_tests + num), "number_of_leaves", len], function (err, result) {
        if (err) throw err;
    });

}
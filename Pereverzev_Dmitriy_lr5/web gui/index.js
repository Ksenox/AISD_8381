var express = require('express');
var app = express();
var path = require('path');
const lrs = require('./build/Release/addon');
//for file
var fs = require('fs');





app.use(express.static(path.join(__dirname, '/front_lrs')));
var bodyParser = require("body-parser");
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());


//MAIN PAGE
app.get('/', function (req, res) {
    res.send(index.html);
});

//PAGES OF LABORATORY WORK 3
app.get('/lr_3_pref', function (req, res) {
    res.sendFile(__dirname + '/front_lrs/labs/lr3screen.html');
});


app.post('/lr_3_pref', function (req, res) {
    var body = req.body;
    var pref_str = "jhgfd";

    if (body.err == 'test') {
        var err = lrs.tester_3(body.pref_str.replace(/ /g, '+'));
        res.end(err.toString(10));
    }
    else {
        if (body.flag) { //step by step
            pref_str = lrs.step_up(body.pref_str.replace(/ /g, '+'));
            res.end(pref_str);

        }
        else { //all steps
            var g = (body.pref_str.replace(/ /g, '+'));
            pref_str = lrs.all_steps(body.pref_str.replace(/ /g, '+'));
            pref_str = pref_str.toString(10);
            res.end(pref_str);

        }
    }
});

//PAGES OF LABORATORY WORK 4

app.get('/lr_4_tree', function (req, res) {
    res.sendFile(__dirname + '/front_lrs/labs/lr4screen.html');
});

app.post('/lr_4_tree', function (req, res) {

    var body = req.body;
    var bin_str = "jhgfd";
    var bypass_width_str;
    //test


    if (body.file) {
        fs.readFile(body.file.value, 'utf8', function (err, file_data) {
            res.end(file_data);
        });



    }
    if (body.err == 'test') {
        var err = lrs.tester_4(body.str);
        res.end(err.toString(10));
    }
    if (body.bin_str) {

        bin_str = lrs.take_bin_str_4(body.bin_str);
        res.end(bin_str);

    }
    if (body.bypass_width_str == "go") {
        bypass_width_str = lrs.width_4(body.bin_str);
        res.end(bypass_width_str);

    }


});

//PAGES OF LABORATORY WORK 5

app.get('/lr_5_tree', function (req, res) {
    res.sendFile(__dirname + '/front_lrs/labs/lr5screen.html');
});

app.post('/lr_5_tree', function (req, res) {

    var body = req.body;
    if (body.string_of_elem) {
        var err = lrs.tester_5(body.string_of_elem, body.string_of_elem.split(' ').length);
        res.end(err.toString(10));
    }
    if (body.elem_for_del) {
        var string_tree = lrs.find_and_del_5(body.elem_for_del);
        res.end(string_tree);
    }
    if (body.build) {
        var string_tree = lrs.build_tree_5(body.build, body.build.split(' ').length - 1);
        res.end(string_tree);
    }



});

//connect to port 3000
app.listen(3000, function () {
    console.log('Serever startd on port 3000!');
});




//end
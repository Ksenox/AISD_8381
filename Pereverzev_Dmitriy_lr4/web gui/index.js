var express = require('express');
var app = express();
var path = require('path');
const lr_3 = require('./build/Release/addon');
//for file
var fs = require('fs');





app.use(express.static(path.join(__dirname, '/front_lrs')));
var bodyParser = require("body-parser");
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());


//connect to port 3000
app.listen(3000, function () {
    console.log('Serever startd on port 3000!');
});

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
        var err = lr_3.tester_3(body.pref_str.replace(/ /g, '+'));
        res.end(err.toString(10));
    }
    else {
        if (body.flag) { //step by step
            pref_str = lr_3.step_up(body.pref_str.replace(/ /g, '+'));
            res.end(pref_str);

        }
        else { //all steps
            var g = (body.pref_str.replace(/ /g, '+'));
            pref_str = lr_3.all_steps(body.pref_str.replace(/ /g, '+'));
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

    if (body.err == 'test') {
        var err = lr_3.tester_4(body.str);
        res.end(err.toString(10));
    }
    if (body.bin_str) {

        bin_str = lr_3.take_bin_str_4(body.bin_str);
        res.end(bin_str);

    }
    if (body.bypass_width_str == "go") {
        bypass_width_str = lr_3.width_4(body.bin_str);
        res.end(bypass_width_str);

    }


});





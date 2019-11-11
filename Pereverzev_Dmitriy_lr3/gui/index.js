var express = require('express');
var app = express();
var path = require('path');
const lr_3 = require('./build/Release/addon');


app.use(express.static(path.join(__dirname, '/front_lrs')));
var bodyParser = require("body-parser");
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());


//connect to port 3000
app.listen(3000, function () {
	console.log('Serever startd on port 3000!');
});

app.get('/', function (req, res) {
	res.send(index.html);
});

app.get('/lr_3_pref', function (req, res) {
	res.sendFile(__dirname + '/front_lrs/labs/lr3screen.html');
});


app.post('/lr_3_pref', function (req, res) {
	var body = req.body;
	var pref_str = "jhgfd";
	if (body.err == 'test') {
		var err = lr_3.tester(body.pref_str.replace(/ /g, '+'));
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
	//to server


});


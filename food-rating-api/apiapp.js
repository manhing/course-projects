var express = require('express');
var QB = require('quickblox');
var bodyParser = require('body-parser');

var app = express();

app.set('port', 3000);

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

var QBApp = {
  appId: 39257,
  authKey: 'Mkhbcg2TUmzbu2h',
  authSecret: 'OzvOZZfOnaq8AR9'
};

var QBUser = {
	login: "cs4962",   
	password: "cs496cs496" 
};

var APItoken = "";



app.get('/food', function(req, res) {

	QB.init(QBApp.appId, QBApp.authKey, QBApp.authSecret, true);
	QB.createSession(QBUser, function(err, result){
		if (err) {
			console.log('Something went wrong: ' + err);
		} else {
			
			APItoken = result.token;

			var filter = {
				sort_desc: 'created_at',
				token: APItoken
			};
			QB.data.list("foodtable", filter, function(error, result){
				if (error) { 
					console.log(error);
			        res.send(error);
				} else {
					console.log(result);
					res.send(result);

				}
			});
		}
	});

});

app.post('/food', function(req, res) {

	QB.init(QBApp.appId, QBApp.authKey, QBApp.authSecret, true);
	QB.createSession(QBUser, function(err, result){
		if (err) {
			console.log('Something went wrong: ' + err);
		} else {

			QB.data.create("foodtable", {foodname: req.body.foodname, price: req.body.price, 
										rating: req.body.rating, restaurantname: req.body.restaurantname, 
										city: req.body.city, state:req.body.state}, 
										function(error, response){
				if (error) {
					console.log(error);
			        res.send(error);
				} else {
					console.log(response); // has json
					res.status(201);
					res.send(response);


				}
			});
		}
		

	});
	
});

app.put('/food/:foodid', function(req, res) {

	var foodid = req.params.foodid;
	var className = "foodtable";
	var param = {_id: req.params.foodid, foodname: req.body.foodname, price: req.body.price, 
										rating: req.body.rating, restaurantname: req.body.restaurantname, 
										city: req.body.city, state:req.body.state};

	QB.init(QBApp.appId, QBApp.authKey, QBApp.authSecret, true);
	QB.createSession(QBUser, function(err, result){
		if (err) {
			console.log('Something went wrong: ' + err);
		} else {

			QB.data.update(className, param, function(error, response){
			    if (error) {
			        console.log(error);
			        res.status(404);
			        res.send(error);
			    } else {
			        console.log(response);
			        res.send("record deleted: " + response);
			    }
			});
		}
	});
	
});

app.delete('/food/:foodid', function(req, res) {

	QB.init(QBApp.appId, QBApp.authKey, QBApp.authSecret, true);
	QB.createSession(QBUser, function(err, result){
		if (err) {
			console.log('Something went wrong: ' + err);
		} else {
			var className = "foodtable";
			var _id = req.params.foodid;
			 
			QB.data.delete(className, _id, function(error, response){
			    if (error) {
			        console.log(error);
			        res.status(404);
			        res.send(error);
			    } else {
			        console.log(response);
			        res.send(response)
			    }
			});
		}
	});

});


app.listen(app.get('port'), function(){
	console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});
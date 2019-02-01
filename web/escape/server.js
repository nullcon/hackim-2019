var express = require('express');
var app = express();
var {VM} = require('vm2');


app.use(express.static('public'));
app.get('/', function (req, res) {
   res.sendFile( __dirname + "/" + "index.html" );
});


app.get('/run',function(req,res){


		var untrusted = req.query.js
		console.log(untrusted)
		if(untrusted){
		  try{
  			if(untrusted.toString().includes("while")){ res.send("nice try"); return}
		 	run = new VM().run(untrusted)
		 	
			//console.log(run.toString());
			res.send(run.toString())	
		  }catch(x){
			console.log(x);
			res.send(x.toString())
		 }

		
	}

});



var server = app.listen(8080, function () {
   var host = server.address().address
   var port = server.address().port
   
   console.log("Example app listening at http://%s:%s", host, port)
})

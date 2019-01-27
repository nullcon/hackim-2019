var express = require('express');
var ESI = require('nodesi');
var app = express();
var os = require( 'os' );
var {VM} = require('vm2');

var networkInterfaces = os.networkInterfaces();
var eth0 = networkInterfaces.eth0[0].address;


var esi = new ESI();

const host = "172.20.0.2";

const blacklist = "<!--esi-->";

app.use(express.static('public'));
app.get('/', function (req, res) {
   res.sendFile( __dirname + "/" + "index.html" );
});




app.get('/post', function (req, res) {
   // Prepare output in JSON format
   response = {
      title:req.query.title,
      description:req.query.description
   };
  
 console.log(response);

if (response.title.toString().includes(blacklist) || response.description.toString().includes(blacklist)){

res.end('Please Dont Scan!');

} else {
esi.process(response.description).then(function(result) {

   res.end(result); 
 });
}
});

app.get('/admin',function(req,res){

	const address = req.connection.remoteAddress

	console.log(eth0)
	console.log(address.split(":")[3])


	if(address.split(":")[3] == host){
		
		var untrusted = req.query.js
		console.log(untrusted)
		if(untrusted){
		  try{
		 	run = new VM().run(untrusted)
		 	
			//console.log(run.toString());
			res.send(run.toString())	
		  }catch(x){
			console.log(x);
			res.send(x.toString())
		 }

		}
		else {
			res.sendFile( __dirname + "/" + "1329812301293asdb1.html")
		}
		 
	}
	else{
		res.send("You are not a admin. you must come from "+address.split(":")[3])
	}

});



var server = app.listen(8080, function () {
   var host = server.address().address
   var port = server.address().port
   
   console.log("Example app listening at http://%s:%s", host, port)
})

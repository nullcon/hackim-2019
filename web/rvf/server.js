var express = require('express');
var ESI = require('./nodesi');
var app = express();
var os = require( 'os' );

var networkInterfaces = os.networkInterfaces();
var eth0 = networkInterfaces.eth0[0].address;


var esi = new ESI({
        logTo: process.stdout
    });

const host = "172.19.0.1";

const blacklists = ["<!--esi-->","assign","var"];

app.use(express.static('public'));
app.get('/', function (req, res) {
   res.sendFile( __dirname + "/" + "index.html" );
});




app.get('/edge', function (req, res) {
   // Prepare output in JSON format
   response = {
      title:req.query.title,
      description:req.query.description
   };
  
 console.log(response);

  for(blacklist in blacklists){

	if (response.title.toString().includes(blacklists[blacklist]) || response.description.toString().includes(blacklists[blacklist])){

		res.end('Please Dont Scan!');
		return

	} 
  }

	 esi.process(response.description).then(function(result) {
   	res.end(result); 
   });

});

app.get('/admin',function(req,res){

	const address = req.connection.remoteAddress

	console.log(eth0)
	console.log(address.split(":")[3])


	var headers=["x-original-url","x-wap-profile","profile","x-arbitrary","x-http-destinationurl","x-forwarded-proto","origin","x-forwarded-host","x-forwarded-server","x-host","proxy-host","destination","proxy","via","x-forwarded-for","true-client-ip","client-ip","x-client-ip","x-real-ip","x-originating-ip","cf-connecting_ip"]
 	 

 	for (check in headers){

		var heads=req.headers[headers[check]]
		if(heads){
			res.send("Still in old school?")
			return;
		}

	}
	
	if(address.split(":")[3] == host){
		
		res.send("hackim19{h0w_Did_y0ou-Get_here}")
		 
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

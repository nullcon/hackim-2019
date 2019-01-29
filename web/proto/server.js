'use strict';

const express = require('express');
const bodyParser = require('body-parser')
const cookieParser = require('cookie-parser');
const path = require('path');
const mongoose = require('mongoose');
  var url="mongodb://db/challenge"

  var schema = new mongoose.Schema({ name: 'string', post: 'string' });
   var MyModel = mongoose.model('posts', schema);




const isObject = obj => obj && obj.constructor && obj.constructor === Object;

function merge(a,b){
 for (var attr in b){   
   if(isObject(a[attr]) && isObject(b[attr])){
      merge(a[attr],b[attr]);
   }
   else{
    a[attr] = b[attr];
 }
 }  
 return a 
} 

function clone(a){
  return merge({},a);
}

function getPost(id){

  mongoose.connect(url);
  var payload={_id:id}
  console.log(payload)
  MyModel.findById(payload,function (err, adventure) {
   console.log(adventure)
   return adventure;

  })


}

// Constants
const PORT = 8080;
const HOST = '0.0.0.0';
const admin = {};

// App
const app = express();
app.use(bodyParser.json())
app.use(cookieParser());

app.get('/',(req,res) => {


    res.send("Get some POSTS here /getPOST");


});

app.get('/getPost',(req,res) => {

  if(!req.query.id){

    res.json({"error":"id is missing (ex: /getPOST?id=5c46e90eeaca9e86b7fc047a)"});
  }
  else{

    var id=req.query.id

    if(id.match("'")){
      if(id.match("--")){
        res.send("Follow The White Rabbit!")
      }
      res.send("Query failed with error:You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near ''' at line 1")
    }

    if (id.match(/^[0-9a-fA-F]{24}$/)) {
      mongoose.connect(url);
      var payload={_id:id}
      console.log(payload)
      MyModel.findById(payload,function (err, adventure) {
      console.log(adventure)
      if(adventure){
       res.send(adventure.post);
        }   
      else{
       res.json({"error":"Not found"});
      }
     })
    }

    else{
      res.json({"error":"Not found"});
    }


    

  }

});


app.use('/a94b5f1371229440d01f9de77e667b2d/', express.static(path.join(__dirname, 'a94b5f1371229440d01f9de77e667b2dviews')))

app.post('/a94b5f1371229440d01f9de77e667b2d/signup', (req, res) => {
  var body = JSON.parse(JSON.stringify(req.body));
  var copybody = clone(body)
  if(copybody.name){
      res.cookie('name', copybody.name).json({"done":"cookie set"}); 
  }
  else{
    res.json({"error":"cookie not set"})
  }
});

app.get('/a94b5f1371229440d01f9de77e667b2d/getFlag', (req, res) => {


    var аdmin=JSON.parse(JSON.stringify(req.cookies))
    
    if(admin.аdmin==1){
      delete Object.prototype.аdmin;
      res.send("hackim19{Prototype_for_the_win}");
    }
    else{
      res.send("You are not authorized"); 
    }

});


app.listen(PORT, HOST);
console.log(`Running on http://${HOST}:${PORT}`);


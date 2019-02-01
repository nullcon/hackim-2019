'use strict';

const express = require('express');
const bodyParser = require('body-parser')
const cookieParser = require('cookie-parser');
const path = require('path');
const mongoose = require('mongoose');
  var url="mongodb://db:22678/challenge"

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

    res.json({"error":"id is missing (ex: /getPOST?id=5c51b9c9144f813f31a4c0e2)"});
  }
  else{

    var id=req.query.id

    if(id.match("'")){
      if(id.match("--")){
        res.send("Wake up Neo... Follow The White Rabbit!")
        return
      }
   
       res.send("Query failed with error:You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version for the right syntax to use near ''' at line 1")
      return
    }

    if (id.match(/^[0-9a-fA-F]{24}$/)) {
      mongoose.connect(url);
      var payload={_id:id}
      console.log(payload)
      MyModel.findById(payload,function (err, adventure) {
        console.log(err)
      console.log(adventure)
      if(adventure){
       res.send(adventure.post);
       return
        }   
      else{
       res.json({"error":"Not found"});
       return
      }
     })
    }

    else{
      res.json({"error":"Not found"});
      return
    }


    

  }

});


app.use('/4f34685f64ec9b82ea014bda3274b0df/', express.static(path.join(__dirname, '4f34685f64ec9b82ea014bda3274b0dfviews')))

app.post('/4f34685f64ec9b82ea014bda3274b0df/signup', (req, res) => {
  var body = JSON.parse(JSON.stringify(req.body));
  var copybody = clone(body)
  if(copybody.name){
      res.cookie('name', copybody.name).json({"done":"cookie set"}); 
  }
  else{
    res.json({"error":"cookie not set"})
  }
});

app.get('/4f34685f64ec9b82ea014bda3274b0df/getFlag', (req, res) => {


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


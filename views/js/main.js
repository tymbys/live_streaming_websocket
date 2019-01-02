function ScaleContentToDevice(){
	scroll(0, 0);
	var content = $.mobile.getScreenHeight() - $(".ui-header").outerHeight() - $(".ui-footer").outerHeight() - $(".ui-content").outerHeight() + $(".ui-content").height();
	$(".ui-content").height(content);
}


$(document).on( "pagecontainershow", function(){
	ScaleContentToDevice();        
});

$(window).on("resize orientationchange", function(){
	ScaleContentToDevice();
});




var ip = location.host;
var CamUri = "ws://"+ip+"/ws"; //"ws://" + ip + "/ws";
//var KeyUri = "ws://" + ip.replace("8888", "8889") + "/ws";
//var KeyUri = "ws://127.0.0.1:9090/ws";
var output;
var cam_socket;
//var key_socket;
var img;

function init()
{
	output = document.getElementById("output");
	img = document.createElement("img");
//img.height = 640;
//img.height = 800;

img.style["height"] = "100%";
img.style["width"] = "100%";
img.style["object-fit"] = "contain";

img.src = "";
output.appendChild(img);
testWebSocket();
//window.setTimeout(sendCommandVector, 1000);
}

function sendCommandVector() {
	if (key_socket.readyState == 1) {
		console.log("SENDING");
		key_socket.send(JSON.stringify(vector));
		window.setTimeout(sendCommandVector, 100);
	} else {
		console.log("CONNECTION FAILED");
	}
}

function testWebSocket()
{
	console.log("CamUri: "+CamUri);
	cam_socket = new WebSocket(CamUri);
	cam_socket.onopen = function(evt) { onOpen(evt) };
	cam_socket.onclose = function(evt) { onClose(evt) };
	cam_socket.onmessage = function(evt) { onMessage(evt) };
	cam_socket.onerror = function(evt) { onError(evt) };

//cam_socket.binaryType = 'arraybuffer';

//    key_socket = new WebSocket(KeyUri);
//    key_socket.on_open = function(evt) {
//      console.log("Command link established.");
//   }
//    key_socket.on_error = function(evt) {
//      console.log("Command error");
//    }
//    key_socket.on_close = function(evt) {
//      console.log("Command link lost");
//    }
}

function onOpen(evt)
{
	writeToScreen("CAM CONNECTED");
}

function onClose(evt)
{
	writeToScreen("CAM DISCONNECTED");
}

function onMessage(evt)
{
	var outDiv = document.getElementById("output");
	var image = evt.data;
//var imageURL = URL.createObjectURL(image);


/*if(typeof event.data === 'string' ) {
console.log("Received data string");
}else
if(event.data instanceof ArrayBuffer ){
//var buffer = event.data;
console.log("Received arraybuffer");
}*/


//img.src = imageURL;

//var tmp = "data:image/jpeg;base64,";


//img.src ="data:image/jpeg;base64," + JSON.parse(evt.data);
img.src ="data:image/jpeg;base64," + evt.data;

img.onload = function(e) {
//window.URL.revokeObjectURL(this.imageURL);
}

//console.log(evt.data);
//console.log(JSON.parse(evt.data));
//console.debug("WebSocket message received:", event);
}

function onError(evt)
{
	writeToScreen('<span style="color: red;">ERROR:</span> ' + evt.data);
}

function writeToScreen(message)
{
	var pre = document.createElement("p");
	pre.style.wordWrap = "break-word";
	pre.innerHTML = message;
//output.appendChild(pre);

$("#output_status").html(message);
}

window.addEventListener("load", init, false);
window.addEventListener("keydown", onKeyDown, false);
window.addEventListener("keyup", onKeyUp, false);
var vector=[255,0,0,0,0];
function onKeyDown(event){
	var keyCode=event.keyCode;
	switch(keyCode){
case 87: //w
vector[1] = 1;
break;

case 65: //a
vector[3]=1;
break;

case 83: //s
vector[2]=1;
break;

case 68: //d
vector[4]=1;
break;

//case 38: //Up Arrow
//vector[2]=1;
//break;

//case 40: //Down Arrow
//vector[2]=-1;
//break;
}
console.log(vector.toString());
//commandAPI.thrust = vector;

}

function onKeyUp(event){
	var keyCode=event.keyCode;
	switch(keyCode){
case 87: //w
vector[1] = 0;
break;

case 65: //a
vector[3]=0;
break;

case 83: //s
vector[2]=0;
break;

case 68: //d
vector[4]=0;
break;

//case 38: //Up Arrow
//vector[2]=0;
//break;

//case 40: //Down Arrow
//vector[2]=0;
//break;
}
console.log(vector.toString());
//commandAPI.thrust = vector;
}


// Initialize Firebase
var config = {
  apiKey: "AIzaSyCXn3p3qNddV12pnwnellYMzVeL-PK3S1w",
  authDomain: "antiwetw.firebaseapp.com",
  databaseURL: "https://antiwetw.firebaseio.com",
  projectId: "antiwetw",
  storageBucket: "antiwetw.appspot.com",
  messagingSenderId: "1057876156381"
};
firebase.initializeApp(config);

$(document).ready(function(){
  var database = firebase.database();
  var status;
  var rain;
  var flag;
  var val = $('input[name=radio]:checked').val();
  $("#btnWindow").prop("disabled", true);
  $("#btnWindow").css("background-color", "#354052");
  $("#btnWindow").css("opacity", "0.33");
  firebase.database().ref().child("mode").set(parseInt(val));

  $( "input" ).on( "click", function() {
    var val = parseInt($('input[name=radio]:checked').val());
    console.log(val);
    firebase.database().ref().child("mode").set(val);
    if(val){
      $("#btnWindow").prop("disabled", false);
      $("#btnWindow").css("background", "#2b54d0");
      $("#btnWindow").css("opacity", "1");
  }
  else{
      $("#btnWindow").prop("disabled", true);
      $("#btnWindow").css("background-color", "#354052");
      $("#btnWindow").css("opacity", "0.33");
  }


});


  database.ref().on("value", function(snap){
    rain = snap.val().rain;
    if(rain){
      $("#rain_status").text("สภาพอากาศ : ฝนตก");
  } else {
      $("#rain_status").text("สภาพอากาศ : ฝนไม่ตก");
  }
});

  database.ref().on("value", function(snap){
    wds = snap.val().window;
    if(wds){
      $("#window_status").text("หน้าต่าง : ปิด");
  }
  else{
      $("#window_status").text("หน้าต่าง : เปิด");
  }
});

  $("#btnWindow").click(function(){
    var firebaseCom = firebase.database().ref().child("firebaseCommand");
    firebaseCom.set(1);
    if(wds){
      firebase.database().ref().child("window").set(0);
  }
  else{
      firebase.database().ref().child("window").set(1);
  }
    // if(wds == 1){
    //   firebaseRef.set(0);
    //   firebaseCom.set(1)
    //   wds = 0;
    // } else {
    //   firebaseRef.set(1);
    //   firebaseCom.set(2)
    //   wds = 1;
    // }
});
});
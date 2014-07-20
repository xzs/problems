$(document).ready(function() {

  $("#up_btn").click(function () {
    $("#filename").trigger('click');
  });
  $("#up_tmp_btn").click(function () {
    $("#templatefile").trigger('click');
  });


  $("#filename").on("change", function(e){ 
    var ext = $("input#filename").val().split(".").pop().toLowerCase();

    if($.inArray(ext, ["csv"]) == -1) {
      alert('Please upload a .csv format file');
      return false;
    }

    if (e.target.files != undefined) {
      var reader = new FileReader();
      reader.onload = function(e) {
        var csvval=e.target.result.split("\n");
        var mail_list="";

        for(var i=1; i<csvval.length-1;i++){
          var temp = csvval[i+1];
          var mail_list = mail_list+","+temp;
        }

        $("#csvimporthint").html(mail_list).hide();
        alert("Successful mailing list upload!");

      };
      reader.readAsText(e.target.files.item(0));
    }

    return false;
  });  


  $("#templatefile").on("change", function(e){ 
    var ext = $("input#templatefile").val().split(".").pop().toLowerCase();

    if($.inArray(ext, ["txt"]) == -1) {
      alert('Please upload a .txt format file');
      return false;
    }

    if (e.target.files != undefined) {
      var reader = new FileReader();
      reader.onload = function(e) {
        var txtval=e.target.result;
        $("#templateimporthint").html(txtval).hide();
        alert("Successful template upload!");
      };
      reader.readAsText(e.target.files.item(0));
    }
    return false;
  }); 
});


function sendMail(){
  var recipients = $("#csvimporthint").html();
  var subject = $("#esubject").val()
  var content = $("#templateimporthint").html();
  window.location.href = 'mailto:'+recipients+'?subject='+subject+'&body='+content; 
}
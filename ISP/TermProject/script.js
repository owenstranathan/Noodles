
function validate()
{
  alert("In validate");
	var fn = document.getElementById("fname");
	var ln = document.getElementById("lname");
	if(!validateUserID())
  {
    return false;
  }
  if(!validateName(fn))
  {
    return false;
  }
  if(!validateName(ln))
  {
    return false;
  }
  if(!validateEmail())
  {
    return false;
  }
	if(!validatePhone())
  {
    return false;
  }
  if(!validateAddress())
  {
    return false;
  }
	return true;
}

function validateUserID()
{
	var u_id = document.getElementById("userid");
	var pattUser = /([a-zA-Z0-9-])+/;
	if(!pattUser.test(u_id.value))
	{
		alert("Invalid User name!");
		u_id.style.borderColor = "red";
		return false;
	}
	else
	{
		u_id.style.borderColor = "inherit";
	}
	return true;
}

function validateName(name)
{
	var pattName = /[A-Z]{1}/
	if(!pattName.test(name.value)){
    	alert("Invalid name must be capitalized");
    	name.style.borderColor = "red";
    	return false;
  	}
  	else{
    	name.style.borderColor = "inherit";
  	}
  	return true;
}

function validateEmail(){
	var email = document.getElementById("email");
  	var pattEmail = /([a-zA-Z0-9-]*@{1}([a-zA-Z0-9-])*.{1}([a-zA-Z0-9-])+)/i;
  	if(!pattEmail.test(email.value)){
    	alert("Invalid email: must be of the form someone@somewhere.domain");
    	email.style.borderColor = "red";
    	return false;
  	}
  	else{
    	email.style.borderColor = "black";
  	}
  	return true;
}

function validatePhone(){
  	var phone = document.getElementById("phone");
  	var pattPhone =/(([0-9-]){3}(\x2D){1}([0-9-]){3}(\x2D){1}([0-9-]){4})/i;
  	if(!pattPhone.test(phone.value))
  	{
    	alert("Invalid phone: must be of form 555-555-5555");
    	phone.style.borderColor = "red";
    	return false;
  	}
  	else
  	{
    	phone.style.borderColor = "black";
  	}
  return true;
}

function validateAddress()
{
  	var str = document.getElementById("street");
	var cty = document.getElementById("city");
	var st = document.getElementById("state");
	var zp = document.getElementById("zip");
	var pattCity = /[A-Z]{1}/
	var pattState = /[A-Z]{2}/
	var pattZip = /[0-9-]{5}/
 	if(str.value === undefined || str.value==="")
 	{
    	alert("Invalid street name");
    	str.style.borderColor = "red";
    	return false;
  	}
  	else
  	{
    	str.style.borderColor = "black";
  	}
  	if(!pattCity.test(cty.value))
  	{
  		alert("City must begin with a capital letter!");
  		cty.style.borderColor = "red";
  		return false;
  	}
  	else
  	{
  		cty.style.borderColor = "black";
  	}
  	if(!pattState.test(st.value))
  	{	
  		alert("State must be 2 capital letters");
  		st.style.borderColor = "red";
  		return false;
  	}
  	else
  	{
  		st.style.borderColor = "black";
  	}
  	if(!pattZip.test(zp.value))
  	{
  		alert("Zip code must be 5 digits");
  		zp.style.borderColor = "red";
  		return false;
  	}
  	else
  	{
  		zp.style.borderColor = "black";
  	}
  	return true;
}
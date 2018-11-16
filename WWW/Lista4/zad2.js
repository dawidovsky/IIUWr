function check_account() {
	let x = document.getElementById("account");
	let reg = /^[0-9]{26}$/;
	let y = document.getElementById("account_false");
	if(reg.exec(x.value.replace(/\s/g,''))){
		y.innerText = "Prawidłowo!";
		return true;
	}
	y.innerText = "Błędna wartość!";
	return false;
}

function check_pesel() {
	let x = document.getElementById("pesel");
	let reg = /^[0-9]{11}$/;
	let y = document.getElementById("pesel_false");
	if(reg.exec(x.value)){
		y.innerText = "Prawidłowo!";
		return true;
	}
	y.innerText = "Błędna wartość!";
	return false;
}

function check_mail() {
	let x = document.getElementById("mail");
	let reg = /^[a-z0-9.-_]+@[a-z]+\.[a-z]{2,}$/;
	let y = document.getElementById("mail_false");
	if(reg.exec(x.value)){
		y.innerText = "Prawidłowo!";
		return true;
	}
	y.innerText = "Błędna wartość!";
	return false;
}

function check_date() {
	let x = document.getElementById("date");
	let reg = /^[0-9]{4}-[0-9]{2}-[0-9]{2}$/;
	let y = document.getElementById("date_false");
	if(reg.exec(x.value)){
		y.innerText = "Prawidłowo!";
		return true;
	}
	y.innerText = "Błędna wartość!";
	return false;
}

function send() {
	let x = document.getElementById("send_message");
	if(check_account() && check_date() && check_mail() && check_pesel())
		x.innerHTML = "Wysłano!";
	else
		x.innerText = "Są błędy! Popraw je.";
}
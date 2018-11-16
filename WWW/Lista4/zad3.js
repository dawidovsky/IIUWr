var x;
var s = 0;
var m = 0;
var ms = 0;
var game_not_running = true;
var score = 10;
var penalty = 0;
var backed = true;
var end = false;
var outside = true;

function start(){
	outside = false;
	if(game_not_running){
		start_timer();
		make_squares();
		game_not_running = false;
	}
	else if(!end) {
		check_score();
		backed = true;
	}
}

function out(){
	outside = true;
	start_timer();
}

function start_timer(){
	if(outside && !end)
		x = setTimeout(timer, 10);
}

function timer() {
	let y = document.getElementById("timer");
	ms += 10;
	if(ms === 1000){
		ms = 0;
		s++;
	}
	if(s === 60){
		s = 0;
		m++;
	}
	let min = m;
	let sec = s;
	let msec = ms;
	if(min < 10) min = "0"+ m;
	if(sec < 10) sec = "0"+ s;
	if(msec < 10) msec = "00" + ms;
	else if(msec < 100) msec = "0" + ms;
	y.innerHTML = min + ":" + sec + ":" + msec + " penalty: " + penalty;
	
	start_timer();
}

function make_squares(){
	let squares = [];
	let game = document.getElementById("game");
	for(let i=0; i<10; i++){
		let sq = document.createElement("div");
		sq.setAttribute("class", "squ");
		sq.style.setProperty("background-color", "red");
		sq.setAttribute("onmouseover", "mouseoversq(this)");
		position(sq, squares);
		game.appendChild(sq);
		squares.push(sq);
	}
}

function position(squ, tab){
	let x;
	let y;
	do{
		x = Rnd();
		y = Rnd();
	
		while(x > 91)
			x = Rnd();
		if(x > 30 && x < 63)
			while((y > 3 && y < 37) || y > 38)
				y = Rnd();
		else
			while(y > 38)
				y = Rnd();
	}while(!check_position(x, y, tab));
	console.log(x + " " + y)  
	squ.style.setProperty("left", x+"vw");
	squ.style.setProperty("top", y+"vw");
}

function check_position(x, y, tab){
	if(tab.length > 0)
		return tab.every(element => {
			let l = parseInt(element.style.getPropertyValue("left"));
			let t = parseInt(element.style.getPropertyValue("top"));
			if( x < l - 6 || x > l + 6 )
				return true;
			else if(y < t - 6 || y > t + 6)
				return true;
			return false;
		});
	return true;
}

function Rnd() {
    return Math.floor(Math.random() * 101) + 2;
}

function check_score() {
	if( score === 0 ){
		end = true;
		clearTimeout(x);
		let z = document.getElementById("history");
		let y = document.createElement("li");
		let msec = ms;
		if (ms < 10) msec = "00" + ms;
		else if (ms < 100) msec = "0" + ms;
		y.innerHTML = "Time: " + (m < 10 ? "0" + m : m) + ":" + (s < 10 ? "0" + s : s) + ":" + msec + ". Penalty: " + penalty;
		z.appendChild(y);
		let bt = document.createElement("button");
		bt.setAttribute("onclick", "restart()");
		bt.setAttribute("id", "restart");
		bt.innerText = "Restart";
		document.getElementById("game").appendChild(bt);
	}
}

function mouseoversq(sq){
	if(sq.style.getPropertyValue("background-color") === "red" && backed){
		sq.style.setProperty("background-color", "blue");
		score--;
		backed = false;
	}
	else if(score > 0)
		penalty += 5;
}

function restart(){
	score = 10;
	s = 0;
	m = 0;
	ms = 0;
	penalty = 0;
	game_not_running = true;
	backed = true;
	end = false;
	let sqr = document.getElementsByClassName("squ");
	let len = sqr.length;
	for(let i=0;i<len;i++)
		sqr[0].remove();
	let bt = document.getElementById("restart");
	bt.remove();
	let tim = document.getElementById("timer");
	tim.innerText = "00:00:000 penalty: 0";
}
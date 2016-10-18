<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy.php", ["title" => "Buy"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
		if(!preg_match("/^\d+$/", $_POST["shares"])) {
			apologize("Please enter a non-negative integer");
		}
		$buy = strtoupper($_POST["symbol"]);
		$stock = lookup($buy);
		$cash = CS50::query("SELECT cash FROM users WHERE id = " . $_SESSION["id"]);
		$pay = $stock["price"] * $_POST["shares"];
		if($cash[0]["cash"] < $pay) {
			apologize("You can't afford that!");
		} else {
			CS50::query("INSERT INTO home (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $buy, $_POST["shares"]);
			CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $pay, $_SESSION["id"]);
			// record history
			CS50::query("INSERT INTO history (user_id, type, symbol, shares, price, date) VALUES(?, 'BUY', ?, ?, ?, ?)", $_SESSION["id"], $buy, $_POST["shares"], $stock["price"], date ("Y-m-d H:i:s", time()));
		}
		
        redirect("index.php");
	}
	
?>
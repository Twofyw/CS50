<?php

    // configuration
    require("../includes/config.php"); 

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("donate.php", ["title" => "Donate!"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
		if(!preg_match("/^\d+$/", $_POST["money"])) {
			apologize("Please enter a non-negative integer");
		}
		$cash = CS50::query("SELECT cash FROM users WHERE id = " . $_SESSION["id"]);
		if($cash[0]["cash"] < $_POST["money"]) {
			apologize("You think you're rich?");
		} else {
			CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $_POST["money"], $_SESSION["id"]);
			// record history
			CS50::query("INSERT INTO history (user_id, type, symbol, shares, price, date) VALUES(?, 'DONATE', 'Cash', '$$$', ?, ?)", $_SESSION["id"], $_POST["money"], date ("Y-m-d H:i:s", time()));
		}
		
        redirect("index.php");
	}
	
?>
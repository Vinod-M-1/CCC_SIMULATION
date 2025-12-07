function createAccount() {
    let name = document.getElementById("name").value.trim();
    let acc = document.getElementById("acc").value.trim();
    let pin = document.getElementById("pin").value.trim();
    let bal = document.getElementById("bal").value.trim();

    if (!name || !acc || !pin || bal === "") {
        alert("Please fill every field.");
        return;
    }

    let accounts = JSON.parse(localStorage.getItem("accounts")) || [];

    if (accounts.some(a => a.acc === acc)) {
        alert("Account number already exists!");
        return;
    }

    let newUser = {
        name,
        acc,
        pin,
        balance: Number(bal),
        role: "user",
        transactions: []
    };

    accounts.push(newUser);
    localStorage.setItem("accounts", JSON.stringify(accounts));

    alert("Account created successfully!");
    location.href = "login.html";
}

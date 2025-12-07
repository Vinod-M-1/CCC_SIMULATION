// Ensure default admin exists
(function initializeAdmin() {
    let accounts = JSON.parse(localStorage.getItem("accounts")) || [];

    const adminExists = accounts.some(a => a.role === "admin");

    if (!adminExists) {
        accounts.push({
            name: "Administrator",
            acc: "admin",
            pin: "0000",
            balance: 0,
            role: "admin",
            transactions: []
        });
        localStorage.setItem("accounts", JSON.stringify(accounts));
    }
})();

function login() {
    let acc = document.getElementById("acc").value.trim();
    let pin = document.getElementById("pin").value.trim();

    if (acc === "" || pin === "") {
        alert("Enter all fields");
        return;
    }

    let accounts = JSON.parse(localStorage.getItem("accounts")) || [];
    let user = accounts.find(a => a.acc === acc && a.pin === pin);

    if (!user) {
        alert("Invalid account number or PIN");
        return;
    }

    sessionStorage.setItem("user", JSON.stringify(user));

    if (user.role === "admin") {
        location.href = "admin.html";
    } else {
        location.href = "user.html";
    }
}

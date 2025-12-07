// ===================== SECURITY CHECK ======================
let user = JSON.parse(sessionStorage.getItem("user"));
if (!user) location.href = "login.html";

document.getElementById("welcomeTitle").innerText = `Hello, ${user.name} 👋`;
document.getElementById("accNum").innerText = user.acc;

// ===================== NAVIGATION ===========================
function showPage(page) {
    document.querySelectorAll(".page").forEach(p => p.classList.remove("visible"));
    document.getElementById(page).classList.add("visible");

    document.querySelectorAll(".menu li").forEach(li => li.classList.remove("active"));
    event.target.classList.add("active");
}

// ===================== REFRESH USER DATA ====================
function refreshUser() {
    let accounts = JSON.parse(localStorage.getItem("accounts")) || [];
    user = accounts.find(a => a.acc === user.acc);
    sessionStorage.setItem("user", JSON.stringify(user));
    document.getElementById("balance").innerText = "₹" + user.balance;
}
refreshUser();

// ===================== STACK PUSH FUNCTION ==================
function pushTransaction(type, details, amount) {
    let accounts = JSON.parse(localStorage.getItem("accounts"));
    let u = accounts.find(a => a.acc === user.acc);

    // LIFO → Add to TOP of stack
    u.transactions.unshift({
        type,
        details,
        amount,
        time: new Date().toLocaleString()
    });

    localStorage.setItem("accounts", JSON.stringify(accounts));
}

// ===================== DEPOSIT ===============================
function deposit() {
    let amt = Number(document.getElementById("depositAmount").value);
    if (amt <= 0) return alert("Invalid amount");

    let accounts = JSON.parse(localStorage.getItem("accounts"));
    let u = accounts.find(a => a.acc === user.acc);

    u.balance += amt;
    localStorage.setItem("accounts", JSON.stringify(accounts));

    pushTransaction("Deposit", "Cash added to account", amt);

    alert("Deposit successful");
    refreshUser();
    loadTransactions();
}

// ===================== WITHDRAW ==============================
function withdraw() {
    let amt = Number(document.getElementById("withdrawAmount").value);

    if (amt <= 0) return alert("Invalid amount");
    if (amt > user.balance) return alert("Insufficient balance");

    let accounts = JSON.parse(localStorage.getItem("accounts"));
    let u = accounts.find(a => a.acc === user.acc);

    u.balance -= amt;
    localStorage.setItem("accounts", JSON.stringify(accounts));

    pushTransaction("Withdraw", "Cash withdrawn", amt);

    alert("Withdrawal successful");
    refreshUser();
    loadTransactions();
}

// ===================== TRANSFER ==============================
function transfer() {
    let recvAcc = document.getElementById("receiverAcc").value.trim();
    let amt = Number(document.getElementById("transferAmount").value);

    if (!recvAcc || amt <= 0) return alert("Invalid input");
    if (recvAcc === user.acc) return alert("Cannot transfer to your own account");
    if (amt > user.balance) return alert("Insufficient balance");

    let accounts = JSON.parse(localStorage.getItem("accounts"));

    let sender = accounts.find(a => a.acc === user.acc);
    let receiver = accounts.find(a => a.acc === recvAcc);
    if (!receiver) return alert("Receiver account not found");

    sender.balance -= amt;
    receiver.balance += amt;

    // Sender stack entry
    sender.transactions.unshift({
        type: "Sent",
        details: `To ${receiver.name} (${receiver.acc})`,
        amount: amt,
        time: new Date().toLocaleString()
    });

    // Receiver stack entry
    receiver.transactions.unshift({
        type: "Received",
        details: `From ${sender.name} (${sender.acc})`,
        amount: amt,
        time: new Date().toLocaleString()
    });

    localStorage.setItem("accounts", JSON.stringify(accounts));

    alert("Transfer Successful");
    refreshUser();
    loadTransactions();
}

// ===================== LOAD STACK (LIFO) ====================
function loadTransactions() {
    let accounts = JSON.parse(localStorage.getItem("accounts"));
    let u = accounts.find(a => a.acc === user.acc);

    let table = document.getElementById("txnTable");
    table.innerHTML = "";

    u.transactions.forEach(txn => {
        table.innerHTML += `
            <tr>
                <td>${txn.type}</td>
                <td>
                    ${txn.details}
                    <br>
                    <small>${txn.time}</small>
                </td>
                <td style="text-align:right;">₹${txn.amount}</td>
            </tr>
        `;
    });
}
loadTransactions();

// ===================== LOGOUT ================================
function logout() {
    sessionStorage.clear();
    location.href = "login.html";
}

// Security check
if (!sessionStorage.getItem("user")) location.href = "login.html";

let admin = JSON.parse(sessionStorage.getItem("user"));
if (admin.role !== "admin") location.href = "login.html";

// Show section
function showSection(id) {
    document.querySelectorAll('.section').forEach(s => s.classList.remove("visible"));
    document.getElementById(id).classList.add("visible");

    document.querySelectorAll(".menu").forEach(m => m.classList.remove("active"));
    event.target.classList.add("active");
}

// Load dashboard info
function loadAdminData() {
    let accounts = JSON.parse(localStorage.getItem("accounts")) || [];

    // Overview Stats
    document.getElementById("totalAccounts").innerText = accounts.length;

    let totalBal = accounts.reduce((sum, a) => sum + a.balance, 0);
    document.getElementById("totalBalance").innerText = "₹" + totalBal;

    let totalTxn = accounts.reduce((sum, a) => sum + a.transactions.length, 0);
    document.getElementById("totalTransactions").innerText = totalTxn;

    // Fill table
    let table = document.getElementById("accountTable");
    table.innerHTML = "";

    accounts.forEach((a, i) => {
        table.innerHTML += `
            <tr>
                <td>${i + 1}</td>
                <td>${a.name}</td>
                <td>${a.acc}</td>
                <td>₹${a.balance}</td>
            </tr>
        `;
    });
}

loadAdminData();

// Search account
function fetchAccount() {
    let acc = document.getElementById("searchAcc").value.trim();
    let accounts = JSON.parse(localStorage.getItem("accounts")) || [];

    let user = accounts.find(a => a.acc === acc);

    let result = document.getElementById("result");

    if (!user) {
        result.innerHTML = `<p class="notfound">No account found.</p>`;
        return;
    }

    result.innerHTML = `
        <div class="detail-card">
            <h3>${user.name}</h3>
            <p><strong>Account:</strong> ${user.acc}</p>
            <p><strong>Balance:</strong> ₹${user.balance}</p>
            <p><strong>Transactions:</strong> ${user.transactions.length}</p>
        </div>
    `;
}

// Logout
function logout() {
    sessionStorage.clear();
    location.href = "login.html";
}

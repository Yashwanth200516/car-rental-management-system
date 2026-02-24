const params = new URLSearchParams(window.location.search);
if (params.get("car")) {
    document.getElementById("carid").value = params.get("car");
    localStorage.setItem("price", params.get("price"));
}

function book() {
    let booking = {
        name: name.value,
        phone: phone.value,
        carid: carid.value,
        days: days.value,
        total: days.value * localStorage.getItem("price")
    };

    let history = JSON.parse(localStorage.getItem("history")) || [];
    history.push(booking);
    localStorage.setItem("history", JSON.stringify(history));

    localStorage.setItem("current", JSON.stringify(booking));
    window.location.href = "bill.html";
}


if (document.getElementById("bill")) {
    let total = localStorage.getItem("days") * localStorage.getItem("price");
    bill.innerHTML = `
    Name: ${localStorage.getItem("name")}<br>
    Phone: ${localStorage.getItem("phone")}<br>
    Car ID: ${localStorage.getItem("carid")}<br>
    Days: ${localStorage.getItem("days")}<br><br>
    <b>Total Amount: ₹${total}</b>`;
}
// DARK MODE
function toggleDarkMode() {
    document.body.classList.toggle("dark-mode");

    if (document.body.classList.contains("dark-mode")) {
        localStorage.setItem("theme", "dark");
    } else {
        localStorage.setItem("theme", "light");
    }
}

// LOAD THEME
if (localStorage.getItem("theme") === "dark") {
    document.body.classList.add("dark-mode");
}
// BILL PAGE
if (document.getElementById("bill")) {
    let b = JSON.parse(localStorage.getItem("current"));
    bill.innerHTML = `
        Name: ${b.name}<br>
        Phone: ${b.phone}<br>
        Car ID: ${b.carid}<br>
        Days: ${b.days}<br><br>
        <b>Total Amount: ₹${b.total}</b><br><br>
        <a href="history.html">View Booking History</a>
    `;
}
// HISTORY PAGE
if (document.getElementById("history")) {
    let history = JSON.parse(localStorage.getItem("history")) || [];
    let rows = "";

    history.forEach(b => {
        rows += `
        <tr>
            <td>${b.name}</td>
            <td>${b.phone}</td>
            <td>${b.carid}</td>
            <td>${b.days}</td>
            <td>₹${b.total}</td>
        </tr>`;
    });

    document.getElementById("history").innerHTML = rows;
}


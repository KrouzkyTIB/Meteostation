const reloadIntervalMs = 10000;
window.setInterval(() => {
    location.reload()
}, reloadIntervalMs)

async function toggleLcdBacklight(){
    const request = await fetch("/toggle-lcd", {
            method: "POST"
    })
    if (request.ok){
        location.reload()
    }else{
        alert("Nepovedlo se změnit stav podsvícení displaye")
    }
}

async function resetWifi(){
    const request = await fetch("/reset-wifi", {
        method: "POST"
    })
    if (request.ok){
        location.reload()
    }else{
        alert("Nepovedlo se resetovat nastavení Wi-Fi")
    }
}
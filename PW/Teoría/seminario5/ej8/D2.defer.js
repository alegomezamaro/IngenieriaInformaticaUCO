console.log('D2 start', performance.now().toFixed(1), document.readyState);
setTimeout(() => {
 console.log('D2 end', performance.now().toFixed(1), document.readyState);
}, 0)
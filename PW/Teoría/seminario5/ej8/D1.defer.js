console.log('D1 start', performance.now().toFixed(1), document.readyState);
setTimeout(() => {
 console.log('D1 end', performance.now().toFixed(1), document.readyState);
}, 0)
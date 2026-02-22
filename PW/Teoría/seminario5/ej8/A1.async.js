console.log('A1 start', performance.now().toFixed(1), document.readyState);
setTimeout(() => {
 console.log('A1 end', performance.now().toFixed(1), document.readyState);
}, 0)
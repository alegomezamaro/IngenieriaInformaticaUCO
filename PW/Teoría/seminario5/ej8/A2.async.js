console.log('A2 start', performance.now().toFixed(1), document.readyState);
setTimeout(() => {
 console.log('A2 end', performance.now().toFixed(1), document.readyState);
}, 0)
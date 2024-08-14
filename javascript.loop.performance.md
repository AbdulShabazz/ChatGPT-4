# Javascript Loop Performance

```javascript
// Setup
const size = 1000000;
const map = new Map();
const obj = {};
const arr = [];

for (let i = 0; i < size; i++) {
  map.set(i, i);
  obj[i] = i;
  arr.push(i);
}

// Helper function to measure performance
function measurePerformance(fn) {
  const start = performance.now();
  fn();
  return `${performance.now() - start} milliseconds`;
}

// Array iterations
console.log('Array for loop:', measurePerformance(() => {
  for (let i = 0; i < arr.length; i++) {}
}));

console.log('Array forEach:', measurePerformance(() => {
  arr.forEach(value => {});
}));

console.log('Array map:', measurePerformance(() => {
  arr.map(value => value);
}));

console.log('Object.keys forEach:', measurePerformance(() => {
  Object.keys(obj).forEach(key => {});
}));

console.log('Object for...in:', measurePerformance(() => {
  for (const key in obj) {}
}));

console.log('Map forEach:', measurePerformance(() => {
  map.forEach((value, key) => {});
}));

// Map iterations
console.log('Map for...of:', measurePerformance(() => {
  for (const [key, value] of map) {}
}));

// Note: Results may vary based on JavaScript engine and hardware

/**
ouput:

Array for loop: 25 milliseconds debugger eval code:21:9
Array forEach: 128 milliseconds debugger eval code:25:9
Array map: 178 milliseconds debugger eval code:29:9
Object.keys forEach: 201 milliseconds debugger eval code:33:9
Object for...in: 213 milliseconds debugger eval code:37:9
Map forEach: 214 milliseconds debugger eval code:41:9
Map for...of: 644 milliseconds debugger eval code:46:9

*/
```

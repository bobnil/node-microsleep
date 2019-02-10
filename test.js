const microsleep = require('./index.js');

function test(delay)
  {
    let ts1 = process.hrtime();
    microsleep(delay);
    let ts2 = process.hrtime();
    return Math.floor((( (ts2[0] - ts1[0]) * 1E9 ) + (ts2[1] - ts1[1])) / 1000);
  }

for (let idx = 0; idx < 7; idx+=1)
  {
    let goal = Math.pow(10, idx) * 2;
    let result = test(goal);
    console.log(
      'Goal: %s, result: %s, diff:%s', 
      goal.toString().padStart(10,' '),
      result.toString().padStart(10,' '),
      (result - goal).toString().padStart(10,' ')
    );
  }

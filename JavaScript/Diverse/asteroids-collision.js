function asteroidCollision(asteroids) {
  const result = [];

  for (const a of asteroids) {
    if (!result.length) {
      result.push(a);
      continue;
    }

    let lastAsteroid = result[result.length - 1];
    const willCollide = lastAsteroid > 0 && a < 0;

    if (!willCollide) {
      result.push(a);
      continue;
    }

    if (lastAsteroid + a === 0) {
      // Both collide
      result.pop();
    } else if (-a > lastAsteroid && a !== lastAsteroid) {
      let isCurrentAsteroidStopped = false;

      while (!isCurrentAsteroidStopped && result.length) {
        if (lastAsteroid < 0 && a < 0) {
          // Both going in the same direction
          isCurrentAsteroidStopped = true;
          result.push(a);
          break;
        }

        if (lastAsteroid < -a) {
          result.pop();
          lastAsteroid = result[result.length - 1];
        } else if (lastAsteroid + a === 0) {
          isCurrentAsteroidStopped = true;
          result.pop();
        } else {
          isCurrentAsteroidStopped = true;
        }
      }

      if (!isCurrentAsteroidStopped) {
        result.push(a);
      }
    }
  }

  return result;
};

// console.log(asteroidCollision([5, 10, -5]), [5, 10])
// console.log(asteroidCollision([8, -8]))
// console.log(asteroidCollision([10, 2, -5]), [10])
// console.log(asteroidCollision([-2, -1, 1, 2]), [-2, -1, 1, 2])
// console.log(asteroidCollision([-2, -2, 1, -2]), [-2, -2, -2])
// console.log(asteroidCollision([-2, -2, 1, -2]), [-2, -2, -2], )
// console.log(asteroidCollision([-2, -2, 1, -2]), [-2, -2, -2]);

#include "raylib.pls"

global 0 -> snake/dead?
global 0.5             -> snake/move/time
global snake/move/time -> snake/move/timer
// Assign to snake/next-direction if you want to change direction
// snake/direction is used for animations
global [0, 1]               -> snake/next-direction
global snake/next-direction -> snake/direction

// The last element is the closest to the head
global []     -> snake/tail
global [0, 0] -> snake/head
global 1      -> snake/growth

global [3, 3] -> snake/food

global const 0.90 -> snake/thickness
global const 0x585858FF -> snake/dead/color
global const 0x00FF00FF -> snake/tail/color
global const 0x00AA00FF -> snake/head/color
global const 0xAA0000FF -> snake/food/color

global 1 -> game/show-fps?
global 1 -> game/show-grid?
global 1 -> game/paused?
global 0 -> game/over?

global const 0x181818FF -> game/background-color1
global const 0x383838FF -> game/background-color2
global const 100 -> game/cell-size

global const 32 -> game/font-size
global const 0xC0C0C0FF-> game/font-color

global const 72 -> game/target-fps

global 1 -> random/seed
// Xorshift 64bit RNG
*(random/int) -> 1:
  random/seed
    (!dup) 13 << ^
    (!dup)  7 >> ^
    (!dup) 17 << ^
    <-> random/seed
  .

*(itos n) -> 1:
  n if 0: "0" .
  0 -> negative?
  n if < 0:
    1 -> negative?
    n -1 * -> n
  end
  "" while n > 0:
    n 10 % '0' + (!prepend)
    n 10 / -> n
  end
  negative? if: '-' (!prepend) end
  .

*(toggle 1) -> 1: if: 0 else: 1 end .

*(lerp a b t) -> 1:
  b a -
    t *
    a +
  .

*(vec2/sum v1 v2) -> 1:
  <- v1 (!unpack 2)
  <- v2 (!unpack 2)
  local x1 y1 x2 y2:
    x1 x2 +
    y1 y2 +
    (!pack 2)
  end
  .

*(vec2/mul v scalar) -> 1:
  <- v (!unpack 2)
  local x y:
    x scalar *
    y scalar *
    (!pack 2)
  end
  .

*(vec2/lerp v1 v2 t) -> 1:
  <- v1 (!unpack 2)
  <- v2 (!unpack 2)
  local x1 y1 x2 y2:
    x1 x2 t (lerp)
    y1 y2 t (lerp)
    (!pack 2)
  end
  .

*(vec2/inv 1) -> 1:
  (!unpack 2) local x y:
    x -1 *
    y -1 *
    (!pack 2)
  end
  .

*(vec2/equals? v1 v2) -> 1:
  <- v1 (!unpack 2)
  <- v2 (!unpack 2)
  local x1 y1 x2 y2:
    x1 if not x2: 0 .
    y1 if not y2: 0 .
  end
  1
  .

*(game/world/width) -> 1:
  (*raylib/get-screen-width)
    game/cell-size /
    (!floor)
  .

*(game/world/height) -> 1:
  (*raylib/get-screen-height)
    game/cell-size /
    (!floor)
  .

*(game/cell/render! pos thickness color):
  1 thickness - game/cell-size * 2.0 /
    -> padding

  pos game/cell-size (vec2/mul)
    [ padding, padding ] (vec2/sum)
    (!unpack 2)
  game/cell-size
    padding 2 * -
    (!dup)
  color
    (*raylib/draw-rectangle!)
  .

*(game/path/render! path thickness color):
  1 thickness - game/cell-size * 2.0 /
    <-> pad-x
     -> pad-y
  
  <- path
    (!empty?) if: .
    (!head) <-> last-pos
      (!prepend)
    while: (!empty?) if: break
      (!head) -> this-pos
        last-pos (!unpack 2)
        this-pos (!unpack 2)
        local x1 y1 x2 y2:
          x1 if > x2: x2 x1 -> x2 -> x1 end
          y1 if > y2: y2 y1 -> y2 -> y1 end

          x1 game/cell-size * pad-x +
          y1 game/cell-size * pad-y +
          x2 x1 - game/cell-size *; game/cell-size pad-x 2 * -; +
          y2 y1 - game/cell-size *; game/cell-size pad-y 2 * -; +
          color
            (*raylib/draw-rectangle!)
        end
      this-pos -> last-pos
    end
  .

*(abs 1) -> 1:
  (!dup) if < 0: -1 * .
  .

*(snake/food/regen!):
  (random/int) (abs) (game/world/width)  %
  (random/int) (abs) (game/world/height) %
    (!pack 2) -> snake/food
  .

*(snake/can-eat?) -> 1:
  snake/food snake/head (vec2/equals?)
  .

*(snake/move-and-grow!):
  <- snake/tail
    if snake/growth > 0:
      snake/head (!append)
      snake/growth 1 - -> snake/growth
    else:
      (!empty?) if not:
        (!head) (!pop)
        snake/head (!append)
      end
    end
  -> snake/tail

  <- snake/head
    snake/direction (vec2/sum)
  -> snake/head

  (snake/can-eat?) if:
    snake/growth 1 + -> snake/growth
    (snake/food/regen!)
  end

  snake/next-direction -> snake/direction
  .

*(snake/hit-wall?) -> 1:
  snake/head (!unpack 2) local hx hy:
    0 if not <= hx: 1 .
    0 if not <= hy: 1 .
    (game/world/width)  if not > hx: 1 .
    (game/world/height) if not > hy: 1 .
  end
  0
  .

*(snake/hit-itself?) -> 1:
  snake/head (!unpack 2) local hx hy:
    snake/tail while: (!empty?) if: break
      (!head) (!unpack 2) local tx ty:
        hx if tx: hy if ty: 1 . end
      end
    end
  end
  0
  .

*(snake/hit?) -> 1:
  (snake/hit-wall?)   if: 1 .
  (snake/hit-itself?) if: 1 .
  0
  .

*(snake/update! delta-time):
  snake/dead? if: .

  snake/move/timer delta-time -
    (!dup) if <= 0:
      (!pop) snake/move/time
      (snake/move-and-grow!)
      (snake/hit?) -> snake/dead?
    end
  -> snake/move/timer
  .

*(snake/render!):
  1 snake/move/timer snake/move/time / -
    -> movement-progress

  snake/tail
    (!empty?) if not:
      snake/head
        (!append)
      if snake/growth <= 0:
        // Animate tail
        (!head)  -> tail1
        (!head) <-> tail2
          (!prepend)
        tail1 tail2 movement-progress (vec2/lerp)
          (!prepend)
      end
    else:
      if snake/growth > 0:
        snake/head
          (!append)
      end
    end
    snake/head
      snake/head snake/direction (vec2/sum)
      movement-progress (vec2/lerp)
      <-> animated-head-position
      (!append)
  snake/thickness snake/dead? if not: snake/tail/color else: snake/dead/color end
    (game/path/render!)

  snake/food snake/thickness snake/food/color
    (game/cell/render!)

  animated-head-position snake/thickness snake/head/color
    (game/cell/render!)

  .

*(game/handle-input!):
  snake/next-direction -> desired-next-direction
  raylib/key/w (*raylib/is-key-pressed?) if: [ 0, -1] -> desired-next-direction end
  raylib/key/s (*raylib/is-key-pressed?) if: [ 0,  1] -> desired-next-direction end
  raylib/key/a (*raylib/is-key-pressed?) if: [-1,  0] -> desired-next-direction end
  raylib/key/d (*raylib/is-key-pressed?) if: [ 1,  0] -> desired-next-direction end
  // Make sure we're not trying to go backwards
  desired-next-direction snake/direction (vec2/inv) (vec2/equals?) if not:
    desired-next-direction -> snake/next-direction
  end

  raylib/key/tab (*raylib/is-key-pressed?) if: game/show-fps?  (toggle) -> game/show-fps?  end
  raylib/key/g   (*raylib/is-key-pressed?) if: game/show-grid? (toggle) -> game/show-grid? end
  raylib/key/q   (*raylib/is-key-pressed?) if: game/paused?    (toggle) -> game/paused?    end
  .

*(game/update!):
  (game/handle-input!)

  game/paused? if: .
  game/over?   if: .

  (*raylib/get-frame-time)
    (snake/update!)

  snake/dead? if: 1 -> game/over? .
  .

*(game/render!):
  game/background-color1 (*raylib/clear-background!)
  game/show-grid? if:
    0 -> use-color1?
    (game/world/width) (game/world/height) local w h:
      0 local y: while y <= h:
        0 local x: while x <= w:
          y 2 % if 0:
            x 2 %     -> use-color1?
          else:
            x 2 % 1 - -> use-color1?
          end

          use-color1? if not:
            [x, y] 1 game/background-color2
              (game/cell/render!)
          end

          x 1 + -> x
        end end // Loop x
        y 1 + -> y
      end end // Loop y
    end
  end

  (snake/render!)

  game/show-fps? if:
    "FPS: " 1 (*raylib/get-frame-time) / (!floor) (itos) (!append)
    10 10 game/font-size game/font-color
      (*raylib/draw-text!)
  end
  .

*(main args):
  800 600 "Snake Game" (*raylib/init-window!)
  game/target-fps if > 0:
    game/target-fps (*raylib/set-target-fps!)
  end
  while: (*raylib/window-should-close?) if: break
    (*raylib/begin-drawing!)
      (game/update!)
      (game/render!)
    (*raylib/end-drawing!)
  end
  (*raylib/close-window!)
  .

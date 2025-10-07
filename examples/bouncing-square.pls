#include "raylib.pls"

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

*(main args):
  800 -> window-width
  600 -> window-height
  0x181818FF -> window-background

  32 -> font-size
  0xDDDDDDFF -> font-color

  50                            -> rect-size
  0xFFCCDDFF                    -> rect-color
  window-width  rect-size - 2 / -> rect-x
  window-height rect-size - 2 / -> rect-y
  300                           -> rect-speed-x
  300                           -> rect-speed-y

  window-width window-height "Hello from Pulsar!"
    (*raylib/init-window!)
  60 (*raylib/set-target-fps!)

  while: (*raylib/window-should-close?) if: break
    (*raylib/begin-drawing!)
      (*raylib/get-screen-width)  -> window-width
      (*raylib/get-screen-height) -> window-height
      window-background (*raylib/clear-background!)

      // Update rect coords
      (*raylib/get-frame-time) -> delta-time
      rect-speed-x delta-time * rect-x +
      rect-speed-y delta-time * rect-y +
      local new-x new-y:
        new-x if <= 0:
          rect-speed-x -1 * -> rect-speed-x
          0                 -> new-x
        end
        new-x rect-size + if >= window-width:
          rect-speed-x -1 *        -> rect-speed-x
          window-width rect-size - -> new-x
        end
        new-y if <= 0:
          rect-speed-y -1 * -> rect-speed-y
          0                 -> new-y
        end
        new-y rect-size + if >= window-height:
          rect-speed-y -1 *         -> rect-speed-y
          window-height rect-size - -> new-y
        end
        new-x -> rect-x
        new-y -> rect-y
      end

      // Draw rect
      rect-x rect-y
      rect-size (!dup)
      rect-color
        (*raylib/draw-rectangle!)

      // Draw FPS
      "FPS: " 1 delta-time / (!floor) (itos) (!append)
      10 10 font-size font-color
        (*raylib/draw-text!)
    (*raylib/end-drawing!)
  end

  (*raylib/close-window!)
  .

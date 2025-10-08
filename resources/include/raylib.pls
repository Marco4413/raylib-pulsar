*(*raylib/init-window! width height title).
*(*raylib/set-target-fps! target-fps).
*(*raylib/get-frame-time) -> 1.
*(*raylib/window-should-close?) -> 1.
*(*raylib/close-window!).

*(*raylib/begin-drawing!).
*(*raylib/get-screen-width) -> 1.
*(*raylib/get-screen-height) -> 1.
*(*raylib/clear-background! color).
*(*raylib/draw-rectangle! x y w h color).
*(*raylib/draw-text! text x y font-size color).
*(*raylib/measure-text text font-size) -> 1.
*(*raylib/end-drawing!).

*(*raylib/is-key-pressed? key) -> 1.

// Taken from https://github.com/raysan5/raylib/blob/c1ab645ca298a2801097931d1079b10ff7eb9df8/src/raylib.h#L573
global const 0 -> raylib/key/null // Key: NULL, used for no key pressed
// Alphanumeric keys
global const 39 -> raylib/key/apostrophe    // Key: '
global const 44 -> raylib/key/comma         // Key: ,
global const 45 -> raylib/key/minus         // Key: -
global const 46 -> raylib/key/period        // Key: .
global const 47 -> raylib/key/slash         // Key: /
global const 48 -> raylib/key/zero          // Key: 0
global const 49 -> raylib/key/one           // Key: 1
global const 50 -> raylib/key/two           // Key: 2
global const 51 -> raylib/key/three         // Key: 3
global const 52 -> raylib/key/four          // Key: 4
global const 53 -> raylib/key/five          // Key: 5
global const 54 -> raylib/key/six           // Key: 6
global const 55 -> raylib/key/seven         // Key: 7
global const 56 -> raylib/key/eight         // Key: 8
global const 57 -> raylib/key/nine          // Key: 9
global const 59 -> raylib/key/semicolon     // Key: ;
global const 61 -> raylib/key/equal         // Key: =
global const 65 -> raylib/key/a             // Key: A | a
global const 66 -> raylib/key/b             // Key: B | b
global const 67 -> raylib/key/c             // Key: C | c
global const 68 -> raylib/key/d             // Key: D | d
global const 69 -> raylib/key/e             // Key: E | e
global const 70 -> raylib/key/f             // Key: F | f
global const 71 -> raylib/key/g             // Key: G | g
global const 72 -> raylib/key/h             // Key: H | h
global const 73 -> raylib/key/i             // Key: I | i
global const 74 -> raylib/key/j             // Key: J | j
global const 75 -> raylib/key/k             // Key: K | k
global const 76 -> raylib/key/l             // Key: L | l
global const 77 -> raylib/key/m             // Key: M | m
global const 78 -> raylib/key/n             // Key: N | n
global const 79 -> raylib/key/o             // Key: O | o
global const 80 -> raylib/key/p             // Key: P | p
global const 81 -> raylib/key/q             // Key: Q | q
global const 82 -> raylib/key/r             // Key: R | r
global const 83 -> raylib/key/s             // Key: S | s
global const 84 -> raylib/key/t             // Key: T | t
global const 85 -> raylib/key/u             // Key: U | u
global const 86 -> raylib/key/v             // Key: V | v
global const 87 -> raylib/key/w             // Key: W | w
global const 88 -> raylib/key/x             // Key: X | x
global const 89 -> raylib/key/y             // Key: Y | y
global const 90 -> raylib/key/z             // Key: Z | z
global const 91 -> raylib/key/left-bracket  // Key: [
global const 92 -> raylib/key/backslash     // Key: '\'
global const 93 -> raylib/key/right-bracket // Key: ]
global const 96 -> raylib/key/grave         // Key: `
// Function keys
global const 32  -> raylib/key/space         // Key: Space
global const 256 -> raylib/key/escape        // Key: Esc
global const 257 -> raylib/key/enter         // Key: Enter
global const 258 -> raylib/key/tab           // Key: Tab
global const 259 -> raylib/key/backspace     // Key: Backspace
global const 260 -> raylib/key/insert        // Key: Ins
global const 261 -> raylib/key/delete        // Key: Del
global const 262 -> raylib/key/right         // Key: Cursor right
global const 263 -> raylib/key/left          // Key: Cursor left
global const 264 -> raylib/key/down          // Key: Cursor down
global const 265 -> raylib/key/up            // Key: Cursor up
global const 266 -> raylib/key/page-up       // Key: Page up
global const 267 -> raylib/key/page-down     // Key: Page down
global const 268 -> raylib/key/home          // Key: Home
global const 269 -> raylib/key/end           // Key: End
global const 280 -> raylib/key/caps-lock     // Key: Caps lock
global const 281 -> raylib/key/scroll-lock   // Key: Scroll down
global const 282 -> raylib/key/num-lock      // Key: Num lock
global const 283 -> raylib/key/print-screen  // Key: Print screen
global const 284 -> raylib/key/pause         // Key: Pause
global const 290 -> raylib/key/f1            // Key: F1
global const 291 -> raylib/key/f2            // Key: F2
global const 292 -> raylib/key/f3            // Key: F3
global const 293 -> raylib/key/f4            // Key: F4
global const 294 -> raylib/key/f5            // Key: F5
global const 295 -> raylib/key/f6            // Key: F6
global const 296 -> raylib/key/f7            // Key: F7
global const 297 -> raylib/key/f8            // Key: F8
global const 298 -> raylib/key/f9            // Key: F9
global const 299 -> raylib/key/f10           // Key: F10
global const 300 -> raylib/key/f11           // Key: F11
global const 301 -> raylib/key/f12           // Key: F12
global const 340 -> raylib/key/left-shift    // Key: Shift left
global const 341 -> raylib/key/left-control  // Key: Control left
global const 342 -> raylib/key/left-alt      // Key: Alt left
global const 343 -> raylib/key/left-super    // Key: Super left
global const 344 -> raylib/key/right-shift   // Key: Shift right
global const 345 -> raylib/key/right-control // Key: Control right
global const 346 -> raylib/key/right-alt     // Key: Alt right
global const 347 -> raylib/key/right-super   // Key: Super right
global const 348 -> raylib/key/kb-menu       // Key: KB menu
// Keypad keys
global const 320 -> raylib/key/kp-0        // Key: Keypad 0
global const 321 -> raylib/key/kp-1        // Key: Keypad 1
global const 322 -> raylib/key/kp-2        // Key: Keypad 2
global const 323 -> raylib/key/kp-3        // Key: Keypad 3
global const 324 -> raylib/key/kp-4        // Key: Keypad 4
global const 325 -> raylib/key/kp-5        // Key: Keypad 5
global const 326 -> raylib/key/kp-6        // Key: Keypad 6
global const 327 -> raylib/key/kp-7        // Key: Keypad 7
global const 328 -> raylib/key/kp-8        // Key: Keypad 8
global const 329 -> raylib/key/kp-9        // Key: Keypad 9
global const 330 -> raylib/key/kp-decimal  // Key: Keypad .
global const 331 -> raylib/key/kp-divide   // Key: Keypad /
global const 332 -> raylib/key/kp-multiply // Key: Keypad *
global const 333 -> raylib/key/kp-subtract // Key: Keypad -
global const 334 -> raylib/key/kp-add      // Key: Keypad +
global const 335 -> raylib/key/kp-enter    // Key: Keypad Enter
global const 336 -> raylib/key/kp-equal    // Key: Keypad =
// Android key buttons
global const 4  -> raylib/key/back        // Key: Android back button
global const 5  -> raylib/key/menu        // Key: Android menu button
global const 24 -> raylib/key/volume-up   // Key: Android volume up button
global const 25 -> raylib/key/volume-down // Key: Android volume down button

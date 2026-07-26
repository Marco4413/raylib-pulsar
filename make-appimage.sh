#!/usr/bin/sh

set -xe

if [ "$#" -lt 1 ]; then
    echo 'No input provided.'
    exit 1
fi

ARCH='x86_64'

APPIMAGETOOL="./dist/appimagetool-$ARCH.AppImage"
APPNAME="$(basename "$1" | sed -E 's/^(.*)\.[^.]*$/\1/')"
APPDIR="dist/$APPNAME.AppDir"
APPOUT="dist/$APPNAME-$ARCH.AppImage"

mkdir -p "$APPDIR"

./libs/cpulsar/pulsar-tools compile --no-debug --optimize-all "-o$APPDIR/app.ntx" -Iresources/include "$1"

mkdir -p "$APPDIR/bin"
mkdir -p "$APPDIR/libs"

cp ./libs/cpulsar/pulsar-tools     "$APPDIR/bin"
cp ./libs/cpulsar/libcpulsar.so    "$APPDIR/bin"
cp ./build/raylib.cpulsar.linux.so "$APPDIR/libs"
cp ./LICENSE.md "$APPDIR"
cp ./README.md  "$APPDIR"

cat > "$APPDIR/AppRun" << 'AppRun'
#!/usr/bin/sh
HERE="$(dirname "$(readlink -f "$0")")"
"$HERE/bin/pulsar-tools" run -lraylib "-L$HERE/libs" "$HERE/app.ntx"
AppRun
chmod u+x "$APPDIR/AppRun"

cat > "$APPDIR/$APPNAME.desktop" << App.Desktop
[Desktop Entry]
Version=1.0
Name=$APPNAME
Type=Application
Exec=AppRun
Icon=$APPNAME
Categories=AudioVideo;Video;
App.Desktop
touch "$APPDIR/$APPNAME.svg"

"$APPIMAGETOOL" "$APPDIR" "$APPOUT"
chmod u+x "$APPOUT"

export DEPEND_HOME=/home/cyy/asacoin
./configure \
--disable-tests \
--with-miniupnpc=yes \
CPPFLAGS="-D_WIN32_WINNT=0x0601 -DWINVER=0x0601 -w -g -O0 -I${DEPEND_HOME}/db4/include/" \
LDFLAGS="-L${DEPEND_HOME}/db4/lib"

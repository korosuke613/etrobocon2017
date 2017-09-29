mv str/apps/include/EtRobocon2017.h str/apps/include/EtRobocon2017.h.bak
cat str/apps/include/EtRobocon2017.h.bak | sed "s/\\/\\/#define IS_RIGHT_COURSE/#define IS_RIGHT_COURSE/" > str/apps/include/EtRobocon2017.h
make app=str side=right
cp str/apps/include/EtRobocon2017.h.bak str/apps/include/EtRobocon2017.h
rm -f str/apps/include/EtRobocon2017.h.bak
mv app app_right
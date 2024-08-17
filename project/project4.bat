@chcp 1251
set /a myrand=23+3*%random%/32768
set "str1=%myrand%&"
set /a myrand=23+3*%random%/32768
set "str2=%myrand%&"
set /a myrand=23+3*%random%/32768
set "str3=%myrand%&"
set /a myrand=23+3*%random%/32768
set "str4=%myrand%&"
set /a myrand=23+3*%random%/32768
set "str5=%myrand%&"
set /a myrand=23+17*%random%/32768
set "str6=%myrand%&"
set /a myrand=23+6*%random%/32768
set "str7=%myrand%&"
set /a myrand=23+3*%random%/32768
set "str8=%myrand%&"
set /a myrand=23+6*%random%/32768
set "str9=%myrand%&"
set /a myrand=23+3*%random%/32768
set "str10=%myrand%&"
set /a myrand=23+3*%random%/32768
set "str11=%myrand%"
set url="file:///C:\Users\Admin\Desktop\git\project\project4.html?%str1%%str2%%str3%%str4%%str5%%str6%%str7%%str8%%str9%%str10%%str11%"
start chrome.exe %url%

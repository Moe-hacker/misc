trap "printf '\033[?25h'&&exit" SIGINT
RGB="254;228;208"
COLOR="\033[1;38;2;${RGB}m"
WIDTH=$(stty size|awk '{print $2}')
HEIGHT=$(stty size|awk '{print $1}')
HEIGHT=$(($HEIGHT-4))
clear
echo -e "${COLOR}\033[?25l╔$(yes "═"|sed $(($WIDTH-2))'q'|tr -d '\n')╗"
printf "║ \033[1;31m○ \033[1;33m○ \033[1;32m○${COLOR}\033[${WIDTH}G║\n"
echo -e "\033[?25l║$(yes "═"|sed $(($WIDTH-2))'q'|tr -d '\n')║"
i=1
while (( $i<=$HEIGHT ));do
i=$(($i+1))
printf "║\033[${WIDTH}G║\n"
done
printf "\033[$(($HEIGHT+4));1H╚$(yes "═"|sed $(($WIDTH-2))'q'|tr -d '\n')╝"
printf "\033[$(($HEIGHT));4H╚$(yes "═"|sed $(($WIDTH-8))'q'|tr -d '\n')╝"
WIDTH=$(($WIDTH-5))
WIDTH_=$(($WIDTH+2))
printf "\033[10;4H║\033[${WIDTH}G\033[1;48;2;114;114;114;38;2;0;0;0m/\\ \033[0m${COLOR}\033[${WIDTH_}G║\n"
printf "\033[11;4H║\033[${WIDTH}G\033[1;48;2;66;66;66m  \033[0m${COLOR}║\n"
WIDTH=$(($WIDTH+5))
i=11
HEIGHT=$(($HEIGHT-3))
WIDTH=$(($WIDTH-5))
while (( $i<=$HEIGHT ));do
i=$(($i+1))
printf "\033[${i};4H║\033[${WIDTH}G\033[1;48;2;114;114;114m  \033[0m${COLOR}║\n"
done
i=$(($i+1))
printf "\033[${i};4H║\033[${WIDTH}G\033[1;48;2;114;114;114;38;2;0;0;0m\\/\033[0m${COLOR}║\n"
printf "\033[9;4H╔$(yes "═"|sed $(($WIDTH-3))'q'|tr -d '\n')╗"
echo -e "\033[7;5H适用的声明和许可条款"
WIDTH=$(($WIDTH-26))
echo -e "\033[10;${WIDTH}H最后更新日期：2022年12月"
echo -e "\033[11;7Htermux-container许可条款:"
echo -e "\033[13;7H本程序以Apache2.0协议授权。"
echo -e "\033[14;7H参见：\033[4mhttp://www.apache.org/licenses/\033[0m${COLOR}"
echo -e "\033[15;7H您至少需要了解以下几点："
echo -e "\033[17;7H  ● 本程序\`无担保\`。"
echo -e "\033[18;7H  ● \`任何\`由本程序带来的\`任何形式的\`损失，作者概不负责。"
echo -e "\033[19;7H  ● 您应当在遵守当地法律规定的前提下使用本程序。"
echo -e "\033[20;7H  ● \`任何\`由本程序带来的\`任何形式的\`法律责任，作者概不负责。"
echo -e "\033[21;7H  ● 本程序作者保留其著作权，严禁在不遵循其许可的情况下二次分发。"
echo -e "\033[${HEIGHT};7H Copyright 2022 Moe-hacker"
HEIGHT=$(($HEIGHT+5))
echo -e "\033[${HEIGHT};7H \033[1;32m[√]\033[0m${COLOR} 我已阅读并接受许可条款，按回车键同意"
read
printf "\033[?25h"

cmd_/home/engineer/jay/drivers/modules.order := {   echo /home/engineer/jay/drivers/mydriver.ko; :; } | awk '!x[$$0]++' - > /home/engineer/jay/drivers/modules.order

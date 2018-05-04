执行说明：
	两个文件夹分别执行make后生成两个可执行文件：client server
	先在一个终端执行server文件夹中的server
		先转换为root用户，再执行./server ip port
	之后在另一个终端执行client文件夹中的client
		./client ip port		
说明：client和server的ip都是服务器端的ip，并且两端的端口号一致才可以。
使用说明：
	先在client端登录
		用户名：user1
		密码：123
	之后client端可以执行：
		指令                              说明
		ls                           查看server端当前目录的文件
		pwd                          查看client所在的server端的当前路径
		removefilename               删除server端filename文件
		cdpath                       进入到server端的path路径里面（path必须是绝对路径）
		getsfilename                 从server端下载filename文件到client端
		putsfilename                 从client端上传filename到server端
		其他指令                     一律当做无效指令
问题说明：
	一、指令与作用对象之间不能有空格：一旦有空格就会被当做两条指令来处理，如：gets filename会被当做 gets和filename两个指令
	二、断点续传功能的不完全实现：什么是断点续传？
		在客户端登录后执行：getsfilename
		然后随便输入几个字符暂停下载:asdfadsf
		之后继续下载：getsfilename
		这样问题就出现了：第二次下载时，文件会下载到一半就出现地址错误而无法继续下载。
	

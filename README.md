自己用的一些qt窗口类的封装  

# 目录  

> * [I、MMsgBox](#one)  
> * [II、MWaitBox](#two)  


<a name="one"></a>  
# I、MMsgBox  

示例:  
~~~
MMsgBox *box = new MMsgBox(nullptr, "提示", "提示内容", ":/other/ico.icns", 
			MMsgBox::MMsgBoxTypeNone, MMsgBox::MMsgBoxButtonAll);
if (box->exec()) {
	qDebug() << "点击确定";
} else {
	qDebug() << "点击取消或者右上角关闭按钮";
}
~~~

![msgbox](https://github.com/xuzheyang/windowlib/raw/master/other/msgbox.png)  


<a name="two"></a>  
# II、MWaitBox  

示例:  
~~~
MWaitBox *box = new MWaitBox(this, "提示内容", 2, MWaitBox::MWaitBoxTypeAffirm);
box->show();
~~~

![msgbox](https://github.com/xuzheyang/windowlib/raw/master/other/waitbox.png)  

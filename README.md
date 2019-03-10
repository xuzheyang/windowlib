自己用的一些qt窗口类的封装  

# 使用  

1. 把`dist`目录里的文件包含到当前项目中  
2. 把`dist/msgbox/mmsgbox.h`里面的`MMB_IMGFILE`和`MMB_QSSFILE`修改成正确的目录  
3. 把`dist/waitbox/mwaitbox.h`里面的`MWB_IMGFILE`和`MWB_GIFFILE`修改成正确的目录  


# 文档  

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

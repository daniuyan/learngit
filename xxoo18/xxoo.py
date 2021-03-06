#coding=gbk
#使用selenuim模拟登录
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from lxml import etree
import time
import requests

#global变量
browser=webdriver.Firefox()
wait=WebDriverWait(browser,10)

#get_content用来处理网络原密码
def get_content():
    global browser
    global wait
    try:
        wait.until(
            #直到找到ol标签为止
            EC.presence_of_element_located((By.XPATH,'//*[@id="comments"]/ol'))
        )
        #
        print("正在爬取{}".format(browser.current_url))
        page_source=browser.page_source #获取网页源码
        html=etree.HTML(page_source) #解析源码
        #获取到id里含comment字符的li标签，在li中找img标签并获取该标签的src属性，也就是图片链接
        imgs=html.xpath("//li[contains(@id,'comment')]//img/@src")
        download(imgs)  #写一个方法下载连接
    except Exception as e:
        print("错误")
        print(e)
    finally:
        browser.close()
        
#写一个图片下载方法
def download(imgs):
    path="./xxoo/{}" #当前目录下创建xxoo目录
    for img in imgs:
        #后面再修改get方法中的headers
        try: 
            res=requests.get(img)
            content=res.content
        except Exception as e:
            print(e)
            continue
        file_name=img.split("/")[-1] #获取图片名称.属性
        with open(path.format(file_name),"wb") as file:
            file.write(content)
            print(file_name+"成功下载文件")
            time.sleep(0.3)
            
    #该imgs集合处理完毕后，进行翻页操作 previous-comment-page
    #获取下一页按钮
    global browser
    global wait
    next = wait.until(
        #找到class="previous-comment-page的a标签，这个里面就是下一页按钮
        EC.presence_of_element_located((By.XPATH, '//*[@id="comments"]//a[@class="previous-comment-page"]'))
    )
    next.click()
    return get_content()  #继续调用get_content方法
        
        

def main():
    #使用PhantomJS去加载
    #实测发现selenium已经放弃PhantomJS，了，建议使用火狐或者谷歌无界面浏览器。
    #ubantu16.04的版本是65.0.1  查了一下geckmodriver 0.24以上都不能用
    #selenium版本是3.141
    #通过多次测试发现使用版本查了一下geckmodriver0.23可以正常模拟登录
    global browser
    global wait
    browser.set_window_size(1366,768) #设置模拟登录的浏览器尺寸
    #wait=WebDriverWait(browser,10)
    browser.get("http://jandan.net/ooxx") #get简单主页
    get_content()


if __name__=='__main__':
    main()
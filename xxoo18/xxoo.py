#coding=gbk
#ʹ��selenuimģ���¼
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from lxml import etree
import time
import requests

#global����
browser=webdriver.Firefox()
wait=WebDriverWait(browser,10)

#get_content������������ԭ����
def get_content():
    global browser
    global wait
    try:
        wait.until(
            #ֱ���ҵ�ol��ǩΪֹ
            EC.presence_of_element_located((By.XPATH,'//*[@id="comments"]/ol'))
        )
        #
        print("������ȡ{}".format(browser.current_url))
        page_source=browser.page_source #��ȡ��ҳԴ��
        html=etree.HTML(page_source) #����Դ��
        #��ȡ��id�ﺬcomment�ַ���li��ǩ����li����img��ǩ����ȡ�ñ�ǩ��src���ԣ�Ҳ����ͼƬ����
        imgs=html.xpath("//li[contains(@id,'comment')]//img/@src")
        download(imgs)  #дһ��������������
    except Exception as e:
        print("����")
        print(e)
    finally:
        browser.close()
        
#дһ��ͼƬ���ط���
def download(imgs):
    path="./xxoo/{}" #��ǰĿ¼�´���xxooĿ¼
    for img in imgs:
        #�������޸�get�����е�headers
        try: 
            res=requests.get(img)
            content=res.content
        except Exception as e:
            print(e)
            continue
        file_name=img.split("/")[-1] #��ȡͼƬ����.����
        with open(path.format(file_name),"wb") as file:
            file.write(content)
            print(file_name+"�ɹ������ļ�")
            time.sleep(0.3)
            
    #��imgs���ϴ�����Ϻ󣬽��з�ҳ���� previous-comment-page
    #��ȡ��һҳ��ť
    global browser
    global wait
    next = wait.until(
        #�ҵ�class="previous-comment-page��a��ǩ��������������һҳ��ť
        EC.presence_of_element_located((By.XPATH, '//*[@id="comments"]//a[@class="previous-comment-page"]'))
    )
    next.click()
    return get_content()  #��������get_content����
        
        

def main():
    #ʹ��PhantomJSȥ����
    #ʵ�ⷢ��selenium�Ѿ�����PhantomJS���ˣ�����ʹ�û�����߹ȸ��޽����������
    #ubantu16.04�İ汾��65.0.1  ����һ��geckmodriver 0.24���϶�������
    #selenium�汾��3.141
    #ͨ����β��Է���ʹ�ð汾����һ��geckmodriver0.23��������ģ���¼
    global browser
    global wait
    browser.set_window_size(1366,768) #����ģ���¼��������ߴ�
    #wait=WebDriverWait(browser,10)
    browser.get("http://jandan.net/ooxx") #get����ҳ
    get_content()


if __name__=='__main__':
    main()
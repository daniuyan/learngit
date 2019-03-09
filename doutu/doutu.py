#coding=gbk
#爬取这个页面下的表情包http://www.doutula.com/article/list/?page={}
#表情包在<img class="lazy image_dtb img-responsive loaded" src="https://ws1.sinaimg.cn/bmiddle/9150e4e5ly1fd8nsyuvbog204602zjsu.gif" data-original="https://ws1.sinaimg.cn/bmiddle/9150e4e5ly1fd8nsyuvbog204602zjsu.gif" data-backup="http://img.doutula.com/production/uploads/image//2019/03/06/20190306830204_asSMbm.gif!dta" 
#alt="打屁股打屁股" style="height: 170px;" data-was-processed="true">
#而这个img的标签是嵌在一个a标签里面的，a标签的class是list-group-item random_list
#class = "lazy image_dtb img-responsive loaded"
#src = "https://ws1.s..."
#data-original = ""
#data-backup = ""
#alt=""
#style=
#data-was-processed
#标签中的data-属性是用来存储页面或应用程序的私有自定义数据
#所以只需要爬取这个标签的src就可以了
#用到下面几个包
import asyncio   #异步读取
import aiohttp
from lxml import etree  #解析页面
import os  #存储到本地需要用到os模块

headers={
	"User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:65.0) Gecko/20100101 Firefox/65.0"
}


#实现获取某页面的表情包
async def get_face(url):
    print("正在操作{}".format(url))
    async with aiohttp.ClientSession() as s:
        async with s.get(url,headers=headers,timeout=3) as res:
            if res.status==200:
                html=await res.text()
                html_format = etree.HTML(html)
                #找到格式化后的里面的res
                hrefs=html_format.xpath("//a[@class='list-group-item random_list']")
                for link in hrefs:
                    face_url = link.get("href") #获取到表情包组的页面地址
                    #一步步解析文件夹
                    #结果如下<a>
                    #           <div>title
                    #                <div>date</div>
                    #           </div>
                    #           <div random_artical...>
                    #                <div col-xs-6...>
                    #                    <img src...></img>
                    #                </div>
                    #           </div>
                    #        </a>
                    title = link.xpath("//div[@class='random_title']/text()")[0]
                    path='./biaoqing/{}'.format(title.strip()) #在当前目录下简历表情文件夹
                    
                    if not os.path.exists(path):
                        os.mkdir(path)
                        print(path+"目录创建成功")
                    else:
                        pass
                    #此处传入的url已经不是函数传入的参数了，而是在该页面解析出来的子url,所以修改一下这个页面名称
                    async with s.get(face_url,headers=headers,timeout=3) as res:
                        if res.status==200:
                            new_html=await res.text()
                            #<img src="https://ws1.sinaimg.cn/large/9150e4e5gy1g0rlhg0ckrj20kp0foq3m.jpg" alt="睡前玩把游戏" onerror="this.src=''">
                            new_html_format=etree.HTML(new_html)
                            #获取图片所在的标签
                            imgs = new_html_format.xpath("//div[@class='artile_des']")
                            #解析这个标签
                            for img in imgs:
                                try:
                                    #拿到img标签
                                    img=img.xpath("table//img")[0]
                                    #解析这个标签
                                    img_down_url=img.get("src")
                                    img_title=img.get("alt")
                                except Exception as e:
                                    print(e)
                    
                                #根据拿到的图片链接下载图片
                                async with s.get(img_down_url, timeout=3) as res:
                                    img_data = await res.read()
                                    filename = path+"/"+img_title.replace('\r\n',"")+"."+img_down_url.split('.')[-1]
                                    try:
                                        #拼接文件名 path+img_title+链接的最后一个属性
                                        #with open('{}/{}.{}'.format(path,img_title.replace('\r\n',""),img_down_url.split('.')[-1],"wb+")) as file:
                                        with open(filename,'wb+') as file:
                                            #print("打开成功！")
                                            #print(filename)
                                            file.write(img_data)
                                            file.close()
                                    except Exception as e:
                                        print(e)
                        else:
                            pass    
                
            else:
                print("访问失败")            
                

#限制一下并发，实现异步方法x_get_face(url)
sema = asyncio.Semaphore(3)

async def x_get_face(url):
    with(await sema):
        await get_face(url)  #该方法待实现
    

#入口方法
if __name__=='__main__':
    url_format = "http://www.doutula.com/article/list/?page={}"
    urls = [url_format.format(index) for index in range(1,20)]  #先爬20个页面的
    loop = asyncio.get_event_loop()
    tasks = [x_get_face(url) for url in urls]  #实现x_get_face函数
    results = loop.run_until_complete(asyncio.wait(tasks))


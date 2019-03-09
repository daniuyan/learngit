#coding=gbk
#��ȡ���ҳ���µı����http://www.doutula.com/article/list/?page={}
#�������<img class="lazy image_dtb img-responsive loaded" src="https://ws1.sinaimg.cn/bmiddle/9150e4e5ly1fd8nsyuvbog204602zjsu.gif" data-original="https://ws1.sinaimg.cn/bmiddle/9150e4e5ly1fd8nsyuvbog204602zjsu.gif" data-backup="http://img.doutula.com/production/uploads/image//2019/03/06/20190306830204_asSMbm.gif!dta" 
#alt="��ƨ�ɴ�ƨ��" style="height: 170px;" data-was-processed="true">
#�����img�ı�ǩ��Ƕ��һ��a��ǩ����ģ�a��ǩ��class��list-group-item random_list
#class = "lazy image_dtb img-responsive loaded"
#src = "https://ws1.s..."
#data-original = ""
#data-backup = ""
#alt=""
#style=
#data-was-processed
#��ǩ�е�data-�����������洢ҳ���Ӧ�ó����˽���Զ�������
#����ֻ��Ҫ��ȡ�����ǩ��src�Ϳ�����
#�õ����漸����
import asyncio   #�첽��ȡ
import aiohttp
from lxml import etree  #����ҳ��
import os  #�洢��������Ҫ�õ�osģ��

headers={
	"User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:65.0) Gecko/20100101 Firefox/65.0"
}


#ʵ�ֻ�ȡĳҳ��ı����
async def get_face(url):
    print("���ڲ���{}".format(url))
    async with aiohttp.ClientSession() as s:
        async with s.get(url,headers=headers,timeout=3) as res:
            if res.status==200:
                html=await res.text()
                html_format = etree.HTML(html)
                #�ҵ���ʽ����������res
                hrefs=html_format.xpath("//a[@class='list-group-item random_list']")
                for link in hrefs:
                    face_url = link.get("href") #��ȡ����������ҳ���ַ
                    #һ���������ļ���
                    #�������<a>
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
                    path='./biaoqing/{}'.format(title.strip()) #�ڵ�ǰĿ¼�¼��������ļ���
                    
                    if not os.path.exists(path):
                        os.mkdir(path)
                        print(path+"Ŀ¼�����ɹ�")
                    else:
                        pass
                    #�˴������url�Ѿ����Ǻ�������Ĳ����ˣ������ڸ�ҳ�������������url,�����޸�һ�����ҳ������
                    async with s.get(face_url,headers=headers,timeout=3) as res:
                        if res.status==200:
                            new_html=await res.text()
                            #<img src="https://ws1.sinaimg.cn/large/9150e4e5gy1g0rlhg0ckrj20kp0foq3m.jpg" alt="˯ǰ�����Ϸ" onerror="this.src=''">
                            new_html_format=etree.HTML(new_html)
                            #��ȡͼƬ���ڵı�ǩ
                            imgs = new_html_format.xpath("//div[@class='artile_des']")
                            #���������ǩ
                            for img in imgs:
                                try:
                                    #�õ�img��ǩ
                                    img=img.xpath("table//img")[0]
                                    #���������ǩ
                                    img_down_url=img.get("src")
                                    img_title=img.get("alt")
                                except Exception as e:
                                    print(e)
                    
                                #�����õ���ͼƬ��������ͼƬ
                                async with s.get(img_down_url, timeout=3) as res:
                                    img_data = await res.read()
                                    filename = path+"/"+img_title.replace('\r\n',"")+"."+img_down_url.split('.')[-1]
                                    try:
                                        #ƴ���ļ��� path+img_title+���ӵ����һ������
                                        #with open('{}/{}.{}'.format(path,img_title.replace('\r\n',""),img_down_url.split('.')[-1],"wb+")) as file:
                                        with open(filename,'wb+') as file:
                                            #print("�򿪳ɹ���")
                                            #print(filename)
                                            file.write(img_data)
                                            file.close()
                                    except Exception as e:
                                        print(e)
                        else:
                            pass    
                
            else:
                print("����ʧ��")            
                

#����һ�²�����ʵ���첽����x_get_face(url)
sema = asyncio.Semaphore(3)

async def x_get_face(url):
    with(await sema):
        await get_face(url)  #�÷�����ʵ��
    

#��ڷ���
if __name__=='__main__':
    url_format = "http://www.doutula.com/article/list/?page={}"
    urls = [url_format.format(index) for index in range(1,20)]  #����20��ҳ���
    loop = asyncio.get_event_loop()
    tasks = [x_get_face(url) for url in urls]  #ʵ��x_get_face����
    results = loop.run_until_complete(asyncio.wait(tasks))


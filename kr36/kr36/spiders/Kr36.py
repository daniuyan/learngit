# -*- coding: utf-8 -*-
import scrapy
import json
#''' ���벻ͬ��������ֶ�'''
from kr36.items import Kr36Item

class Kr36Spider(scrapy.Spider):
    name = 'Kr36'
    allowed_domains = ['36kr.com']
    start_urls = ['https://36kr.com/api/search-column/mainsite?per_page=100&page=1&_=']

    def parse(self, response):
    	  #response = response.body_as_unicode().replace("'", '"')
        data=json.loads(response.text)
        
        #ȡjson���������Ŀ��Ϣ
        totle=int(data["data"]["total_count"])
        for page in range(2, int(totle/1000)+2): 
            print("������ȡ��{}ҳ".format(page))
            #class scrapy.http.Request(url, callback, method='GET', headers, body, cookies, meta, encoding='utf-8', priority=0, dont_filter=False, errback])
            yield scrapy.http.Request("https://36kr.com/api/search-column/mainsite?per_page=100&page={}&_=".format(str(page)), callback=self.parse_item)

    def parse_item(self,response):
        #�����Լ���Ҫ������
        #response = response.body_as_unicode().replace("'", '"')
        data=json.loads(response.text)
        
        item=Kr36Item()
        for one_item in data["data"]["items"]:
            print(one_item)
            item["app_views_count"] = one_item["app_views_count"] if "app_views_count" in one_item else 0# APP�ۿ�����
            item["mobile_views_count"] = one_item["mobile_views_count"]  if "mobile_views_count" in one_item else 0 # �ƶ��˹ۿ�����
            item["views_count"] = one_item["views_count"]  if "views_count" in one_item else 0  # PC�ۿ�����
            item["column_name"] = one_item["column_name"]  # ���
            item["favourite_num"] = one_item["favourite_num"]  if "favourite_num" in one_item else 0  # �ղ�����
            item["title"] = one_item["title"] # ����
            item["published_at"] = one_item["published_at"]  # ����ʱ��
            item["is_free"] = one_item["is_free"] if "is_free" in one_item else 0# �Ƿ����
            item["username"] = json.loads(one_item["user_info"])["name"]
            yield item
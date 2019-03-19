# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://doc.scrapy.org/en/latest/topics/item-pipeline.html
import os
import csv

import sys
reload(sys)
sys.setdefaultencoding('utf-8')


class Kr36Pipeline(object):
    def __init__(self):
        store_file=os.path.dirname(__file__)+'/spiders/36kr.csv'
        self.file = open(store_file,"a+")
        self.writer = csv.writer(self.file)
        
    def process_item(self, item, spider):
        print("start to save data")
        try:
            self.writer.writerow((
                item["title"],
                item["app_views_count"],
                item["mobile_views_count"],
                item["views_count"],
                item["column_name"],
                item["favourite_num"],
                item["published_at"],
                item["is_free"],
                item["username"]
            ))
            print("save data finished")
        except Exception as e:
            print(e.args)
            print("saving error!")

    def close_spider(self,spider):
        self.file.close()
# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# https://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class Kr36Item(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    app_views_count = scrapy.Field() # APP�ۿ�����
    mobile_views_count = scrapy.Field() # �ƶ��˹ۿ�����
    views_count = scrapy.Field() # PC�ۿ�����
    column_name = scrapy.Field() # ���
    favourite_num = scrapy.Field() # �ղ�����
    title = scrapy.Field() # ����
    published_at = scrapy.Field() # ����ʱ��
    is_free = scrapy.Field() # �Ƿ����
    username = scrapy.Field()

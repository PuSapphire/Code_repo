
#a selenium-based webcrawler designed to download stickers from https://chpic.su

from selenium import webdriver
from selenium.webdriver.common.by import By
from pathlib import Path
from time import sleep
from random import random
import requests

def main() -> None:
    S = requests.session()
    folder = Path() / 'SelResults'
    site = 'https://chpic.su/en/stickers/sticker_collection_url_here'
    dct = dict()
    with webdriver.Firefox() as driver:
        driver.get(site)
        image_boxes = driver.find_elements(By.CLASS_NAME, 'stickers_list_item')
        for box in image_boxes:
            image = box.find_element(By.CSS_SELECTOR, 'img')
            filename = image.get_attribute("alt")
            dct[filename] = dct.get(filename, 0) + 1
            filename = f'{filename}{dct[filename] if dct[filename]!=1 else ""}.webp'
            with open(folder / filename, 'wb') as f:
                f.write(S.get(image.get_attribute('src')).content)
            sleep(0.875 + random())
            
if __name__ == '__main__':
    main()

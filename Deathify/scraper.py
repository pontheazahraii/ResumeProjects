from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support.select import Select
import time

'''
#get link to site you want to scrape from
link = "https://chartmasters.org/most-streamed-artists-ever-on-spotify/"
driver.get(link)

#select "All" from the drop down menu 
select = Select(driver.find_element(by=By.NAME, value = "table_1_length"))
select.select_by_visible_text("All")

#sleep so the site has time to update based on the modifications to the drop down menu 
time.sleep(5)

#find the xpath to the elements of the table
path = "//tbody/tr/td[3]/b"
#collect the artists from the table
artists = driver.find_elements(by=By.XPATH, value=path)

#open a file to write all the artists in 
fin = open('artists.txt', 'a')
for artist in artists:
    print(artist.text, file=fin)

#close all necessary things
fin.close()
'''

''' 
This method scrapes IDs off the spotify website from files 
Parameters: 
- fileName: the file to read from 
'''
def scrapeSpotify(fileName):
    options = Options()
    options.add_argument("--disable-gpu")
    options.add_argument("--disable-extensions")
    options.add_argument("--headless")

    #Chrome driver 
    driver = webdriver.Chrome("chromedriver")
    driver.maximize_window()

    #//div[@id="main"]/div/div/div[4]/div[1]/div[2]/div[2]/div/div/div[1]/main/div[2]/div/div/section/div[2]/div/div/div/div[2]/a/@href
    fout = open(fileName, 'r')
    fin1 = open('artistID.txt','a')
    fin2 = open('failed.txt', 'a')
    lines = fout.readlines()
    for line in lines: 
        line = line.replace(" ", "%20")
        link = "https://open.spotify.com/search/" + line
        driver.get(link)

        time.sleep(3)

        #path = '//html/body/div[3]/div/div[2]/div[3]/div[1]/div[2]/div[2]/div/div/div[2]/main/div[2]/div/div/section[1]/div[2]/div/div/div/div[2]/a'
        try:
            url = driver.find_element(by=By.XPATH, value='//a[starts-with(@href,"/artist/")]').get_attribute("href")
            url_list = url.split('/')
            artistID = url_list[-1]
            print(artistID, file=fin1)
        except Exception:
            print(line, file=fin2)

    fin1.close()
    fin2.close()
    fout.close()
    driver.quit()

''' 
This method scrape and artist ID off the spotify website
Parameters: 
- artistName: the name of an artist 
'''
def scrapeSpotify(artistName):
    options = Options()
    options.add_argument("--disable-gpu")
    options.add_argument("--disable-extensions")
    options.add_argument("--headless")

    #Chrome driver 
    driver = webdriver.Chrome("chromedriver")
    driver.maximize_window()
    
    #//div[@id="main"]/div/div/div[4]/div[1]/div[2]/div[2]/div/div/div[1]/main/div[2]/div/div/section/div[2]/div/div/div/div[2]/a/@href

    artistName = artistName.replace(" ", "%20")
    link = "https://open.spotify.com/search/" + artistName
    driver.get(link)

    time.sleep(5)

    #path = '//html/body/div[3]/div/div[2]/div[3]/div[1]/div[2]/div[2]/div/div/div[2]/main/div[2]/div/div/section[1]/div[2]/div/div/div/div[2]/a'
    try:
        url = driver.find_element(by=By.XPATH, value='//a[starts-with(@href,"/artist/")]').get_attribute("href")
        url_list = url.split('/')
        artistID = url_list[-1]
        return artistID
    except Exception:
        return -1

    driver.quit()

def main():

    import dweepy
    import time
    import datetime

    now = datetime.datetime.now()


    thing = "biodata" # colocar o nome do projeto, o mesmo do dweet.i0 

    if thing =='dev' or len(thing) < 1:
        thing = 'ardumini'
        reading1 = 'Temperature'
        reading2 = 'Temperature'
        reading3 = 'Temperature'
    else:
        reading1 = "Temperatura" #adicionar as métricas  
        reading2 = "Umidade_Do_Ar"
        reading3 = "Umidade_Do_Solo"

    #reading2 = input('Enter metric #2 name: (Humidity) ')
    url = dweepy.get_latest_dweet_for(thing)

    #store the data as a dictionary
    dict = url[0]
    #print(dict)
    #longdate = dict['created']
    #print(longdate)
    #date = longdate[:10]
    #print(date)
    #stamptime = longdate[11:19]
    #print(stamptime)
    tempC = dict['content'][str(reading1)]
    #print(tempC)
    #tempF = (int(tempC)*(9/5))+32
    #print(tempF)
    hum = dict['content'][str(reading2)]
    #print(hum)
    soil = dict['content'][str(reading3)]
    #print(soil)
    #tipo = type(stamptime)

    #print("Status update for",thing)
    print("Data:",now.strftime("%d/%m/%y"))
    print("Hora:",now.strftime("%H:%M:%S"))
    #print("Current brightness is...",brightness)
    print("Temperatura...",tempC,"ºC")
    print("Umidade Do Ar...",hum,"%")
    print("Umidade Do Solo...",soil,)
    if soil <= 350:
        print("O sensor está imerso em água")
    elif soil <= 600:
        print("O solo está úmido")
    elif soil <= 1000:
        print("O solo está seco")
    elif soil > 1000:
        print("O sensor está fora do solo ou desconectado")
    else:
        ()
    print("============================")
    time.sleep(5) #para minutos colocar: 60*nº de minutos desejados
    main()
    
main()

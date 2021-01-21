
# tc@piCorePlayer

curl -i -X POST -H 'Content-Type: application/json' -d \
'{"id":1,"method":"slim.request","params":["piCorePlayer",["status","-",1,"tags:gABbehldiqtyrSuoKLN"]]}' \
http://192.168.31.210:9000/jsonrpc.js

#curl -i -X POST -H 'Content-Type: application/json' -d \
#'{"id":1,"method":"slim.request","params":["piCorePlayer",["status","-",1,"tags:al"]]}' \
#http://192.168.31.210:9000/jsonrpc.js


#curl -i -X POST -H 'Content-Type: application/json' -d \
#'{"id":1,"method":"slim.request","params":["",["serverstatus"]]}' \
#http://piCorePlayer:9000/jsonrpc.js

#curl -i -X POST -H 'Content-Type: application/json' -d \
#'{"id":1,"method":"slim.request","params":["192.168.31.210",["status","-",1,"tags:gABbehldiqtyrSuoKLN"]]}' \
#http://piCorePlayer:9000/jsonrpc.js


#curl -i -X GET -H 'Content-Type: application/json' -d \
#'{"id":1,"method":"slim.request","params":["",["serverstatus","-",1,"tags:gABbehldiqtyrSuoKLN"]]}' \
#http://piCorePlayer:9000/jsonrpc.js

#curl -i -X GET -H 'Content-Type: application/json' -d \
#'{"id":1,"method":"slim.request","params":["piCorePlayer",["status"]]}' \
#http://piCorePlayer:9000/jsonrpc.js

# This works - to get full server status
#curl -i -X GET -H 'Content-Type: application/json' -d \
#'{"id":1,"method":"slim.request","params":["",["serverstatus",0,999]]}' \
#http://piCorePlayer:9000/jsonrpc.js


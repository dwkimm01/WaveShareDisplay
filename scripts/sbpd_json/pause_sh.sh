
# tc@piCorePlayer


curl -i -X POST -H 'Content-Type: application/json' -d \
 '{"id":1,"method":"slim.request","params":["piCorePlayer", ["pause"]]}' \
http://piCorePlayer:9000/jsonrpc.js


#curl -i -X GET -H 'Content-Type: application/json' -d \
# '{"id":1,"method":"slim.request","params":["",["button","jump_fwd"]]}' \
#http://piCorePlayer:9000/jsonrpc.js

# This works
#curl -i -X GET -H 'Content-Type: application/json' -d \
#'{"id":1,"method":"slim.request","params":["",["serverstatus",0,999]]}' \
#http://piCorePlayer:9000/jsonrpc.js



#curl -i -X GET -H 'Content-Type: application/json' -d \
#'{"id":1,"method": "slim.request", "params": ["", ["play"]]}' \
#http://piCorePlayer:9000/jsonrpc.js

#curl -i -X GET -H 'Content-Type: application/json' -d \
#'{"id":1,"method":"slim.request","params":["",["serverstatus","-",1,"tags:gABbehldiqtyrSuoKLN"]]}' \
#http://piCorePlayer:9000/jsonrpc.js

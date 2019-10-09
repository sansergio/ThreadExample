# ThreadExample

The HubSensores project is based on the NXP's router elegible end device's example of the Thread stack.

It was tested with the following CoAP commands:

*coap CON GET fd0e:c013:d008:6bc3:70d8:4b0f:841f:7148 /temperature*

*coap CON GET fd0e:c013:d008:6bc3:70d8:4b0f:841f:7148 /humidity*

*coap CON GET fd0e:c013:d008:6bc3:70d8:4b0f:841f:7148 /config*

*coap CON POST fd0e:c013:d008:6bc3:70d8:4b0f:841f:7148 /config 2000*

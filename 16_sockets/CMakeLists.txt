add_executable(byte_order_conversion byte_order_conversion.c ../unsung_utils/utils.c)
add_executable(insock6_util insock6_util.c)
add_executable(insock_util insock_util.c ../unsung_utils/utils.c)
add_executable(interface_naming interface_naming.c)
add_executable(name_lookup name_lookup.c ../unsung_utils/utils.c)
add_executable(neo_name_lookup neo_name_lookup.c)
add_executable(port_n_service_lookup port_n_service_lookup.c ../unsung_utils/utils.c)
add_executable(sockaddr sockaddr.c)
add_executable(unix_domain_socket unix_domain_socket.c)


add_executable(protocol_lookup protocol_lookup.c ../unsung_utils/utils.c)
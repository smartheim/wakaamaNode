disqus:
title: Lightweight M2M library

# WakaamaNode [![Build Status](https://travis-ci.org/Openhab-Nodes/wakaamaNode.svg?branch=master)](https://travis-ci.org/Openhab-Nodes/wakaamaNode) [![Stability: Active](https://masterminds.github.io/stability/active.svg)](https://masterminds.github.io/stability/active.html)


<style>
.w3-left{float:left!important}
.w3-container:after,.w3-container:before{content:"";display:table;clear:both}
.w3-circle{border-radius:50%}
.w3-container,.w3-panel{padding:0.01em 16px}
.w3-card{box-shadow:0 1px 5px 0 rgba(0,0,0,0.16),0 1px 10px 0 rgba(0,0,0,0.12);max-width:400px;margin:5px;margin-bottom:15px;position:relative;}
.w3-card > hr {margin:0;}
.w3-card > ul {margin-right: .625em;}
.w3-card-4,.w3-hover-shadow:hover{box-shadow:0 4px 10px 0 rgba(0,0,0,0.2),0 4px 20px 0 rgba(0,0,0,0.19)}

@media only screen and (min-width: 60em) {
  .md-sidebar--secondary,.md-sidebar--primary {
    display: none;
  }
  .md-content {
    margin-right: 0;
    margin-left: 0;
  }
}

.card tr:nth-child(even){background-color: #f2f2f2;}

.card tr:hover {background-color: #ddd;}

.bottom-link{border:none;display:inline-block;padding:8px 16px;vertical-align:middle;overflow:hidden;text-decoration:none;color:inherit;background-color:inherit;text-align:center;cursor:pointer;white-space:nowrap;width:100%;padding: .75rem 1.25rem;
    background-color: rgba(0,0,0,.03);
    border-top: 1px solid rgba(0,0,0,.125);position:absolute;bottom:0px;}
.bottom-link:hover{box-shadow:none;color:#000!important;background-color:#ccc!important}

.brands:hover {
    text-decoration: none;
}
.brand-espresiff {
    background-position: 0 -440px!important;
    width: 108px;
}
.brand-arduino {
    background-position: 0 -80px!important;
    width: 60px;
}
.brands {
    background: url(assets/brands.png) no-repeat;
    height: 40px;
    display: inline-block;
    vertical-align: middle;
}
details.info {
    font-size: inherit;
}
</style>

This is a high level Lightweight M2M library with a convenient C and C++ API optimized to run on embedded/constrained devices.
It embeds parts of [Eclipse Wakaama](https://github.com/eclipse/wakaama) for lwm2m protocol details.

??? info "Lightweight M2M is a protocol from the Open Mobile Alliance for M2M/IoT device management and communication"
    <img style="float:left;margin-right:15px;margin-bottom:15px;" src="assets/stack.png">
    It is a convention on top of CoAP/UDP, a light and compact protocol with an efficient resource data model.
    It follows a server/client architecture with Request/Response semantics (GET, POST, PUT, DELETE), as well as observable resources.
    
    Optional DTLS (Datagram TLS) ensures secure communication between LWM2M Servers and LWM2M Clients.
    
    The CoAP/lwM2M data model is explained on the [Object API](https://openhab-nodes.github.io/wakaamaNode/api/about/) page.

<br>
<center><img src="assets/wakaamaNode.svg"></center>
<br>
<div style="display: flex;flex-wrap: wrap;justify-content: space-around;">
    <div>
        <center><big>3 Platform integrations</big></center>
        <center><small>posix/win32, esp8266-sdk, freertos</small></center>
    </div>
    <div>
        <center><big>Supports 2 Network stacks</big></center>
        <center><small>posix/win32, lwIP</small></center>
    </div>
    <div>
        <center><big>2 Firmware update integrations</big></center>
        <center><small>posix/Win32, ESP OTA</small></center>
    </div>
</div>
<br>


<div style="display: flex;flex-wrap: wrap;justify-content: space-around;">

<div class="w3-card">
    <header class="w3-container md-hero md-header-nav__title">
    Connection API
    </header>
    
    <p class="w3-container">
    The connection API hides away complexity of different required lwm2m objects (security, server and device).
    </p>
    
    <hr>
    <ul>
    <li>Connect with Dtls PSK encryption</li>
    <li>UDP and UDP Queue mode support</li>
    <li>Access native socket handlers</li>
    <li>Full network lifetime control</li>
    <li>Reconnect API</li>
    <li>Firmware update object support <a href="/advanced-usage/ota/">👉</a></li>
    <li>Provide device information and state</li>
    </ul>

    <br><br>
    <a href="/api/connection-api/" class="bottom-link">C/C++ Connection/Device/Firmware API</a>
</div>

<div class="w3-card">
    <header class="w3-container md-hero md-header-nav__title">
    Object definition API
    </header>

    <p class="w3-container">
    The object definition API provides elegant macros for C and a sophisticated
    resource efficient class model for C++ to define custom lwm2m objects and resources.<br>
    </p>
    
    <hr>
    <ul>
    <li>The same API is used to provide all lwm2m registry objects.</li>
    <li>Store resource values in object instances or let them be handed over to functions.</li>
    <li>Read resource values from object instances or let those be acquired from function calls.</li>
    </ul>
    
    <br><br>
    <a href="/api/objects-custom/" class="bottom-link">C/C++ Custom Object API</a>
</div>


<div class="w3-card">
    <header class="w3-container md-hero md-header-nav__title">
    OMA Object & Resource Registry
    </header>

    <p class="w3-container">
    Standardised object and resource identifiers via the <a href="http://www.openmobilealliance.org/wp/OMNA/LwM2M/LwM2MRegistry.html">OMA Object & Resource Registry</a>.
    </p>
    <hr>
    
    <center><small>Examples</small></center>
    <table class="card">

    <tr class="card"><td>
    <div class="w3-container" style="padding:5px;">
    <img src="assets/lamp.png" alt="Lamp" class="w3-left" style="padding-right:15px">
    <div style="max-height:100px;overflow: hidden;"><a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3311.xml">Object 3311</a> - Light control<br>
    This Object is used to control a light source, such as a LED or other light. It allows a light to be turned on or off and &hellip;</div>
    </div>
    </td></tr>

    <tr class="card"><td>
    <div class="w3-container" style="padding:5px;">
    <img src="assets/plug.png" alt="Plug" class="w3-left" style="padding-right:15px">
    <div style="max-height:100px;overflow: hidden;"><a href="http://www.openmobilealliance.org/tech/profiles/lwm2m/3312.xml">Object 3312</a> - Power sources
    <br>
    It allows a power relay to be turned on or off and its dimmer setting to be control &hellip;</div>
    </div>
    </td></tr>
    
    <tr class="card"><td>
    <center>&hellip;</center>
    </td></tr>
    
    </table>
    
    <br><br>
    <a href="/api/objects-registry/" class="bottom-link">C++ API for lwm2m registry objects</a>
</div>

<div class="w3-card">
    <header class="w3-container md-hero md-header-nav__title">
    Stability / Low maintenance
    </header>
    
    <ul>
    <li>
    <b>Stable</b>: Object, Connect and internal API fully covered by extensive tests.<br>
    Plain + dtls connection tests against the <em>embedded wakaama</em> and <em>external leshan</em> lwm2m server.
    <a href="/testing/">👉 More info</a>
    </li>

    <li >
    <b>Trust</b>: The library is following the SemVer versioning schema and guarantees no API breakage.
    </li>

    <li>
    <b>Low maintenance</b>: Automatic transformation of newest lwm2m registry objects into c++ classes. Automatic external code sync scripts.<br>
    </li>

    </ul>
</div>

<div class="w3-card">
    <header class="w3-container md-hero md-header-nav__title">
    Embedded in mind
    </header>
    
    <hr>
    <ul>
    <li>Platform/network abstraction<br>
        <a href="/advanced-usage/custom-platform/">👉 Implement your own</a></li>
    <li>Main loop based.<br>
        <a href="/advanced-usage/own-mainloop/">👉 epoll support on Posix/Win32</a></li>
    <li>Full memory control<br>
        <a href="/advanced-usage/memory/">👉 Fixed memory allocation support</a><br>
        <a href="/quickstart/getting-started/#configure-features-with-wakaama_configh">👉 Customize buffers via config file</a></li>
    <li>Slim mono thread design.<br>
        <a href="/advanced-usage/thread-safety/">👉 Prepared for multi-thread object instance access.</a></li>
    </ul>
</div>

<div class="w3-card">
    <header class="w3-container md-hero md-header-nav__title">
    Security
    </header>
    
    <p class="w3-container">
    Automatic, periodic synchronisation to the <a href="https://github.com/ARMmbed/mbed-os/tree/master/features/mbedtls">latest mbedTLS sources</a>.
    </p>
    
    <hr>
    <ul>
    <li>Supports PSK mode with <i>AES_128_CCM_8</i>, <i>AES_128_CBC_SHA256</i></li>
    <li>Supports Raw Public Key Certificates mode ECDHE_ECDSA with <i>AES_128_CCM_8</i>, <i>AES_128_CBC_SHA256</i></li>
    <li><del>Supports X.509v3 Certificates mode</del></li>
    <li>More cipher suits can be enabled in the configuration file</li>
    </ul>
    
    <br><br>
    
    <a href="/advanced-usage/custom-network/#dtls" class="bottom-link">Custom network &rarr; DTLS</a>
</div>

</div>

## Getting started

Head over to the [Get started](quickstart/getting-started.md) page to dive right into installing and including the library in your project.

## License

This library including the platform code, tests and API wrappers are provided under the MIT license.
Wakaama is provided under the Eclipse Public License - v2.0.

<center>
<picture>
  <source srcset="assets/logo_s.webp" type="image/webp">
  <source srcset="assets/logo_s.png" type="image/png"> 
  <img src="assets/logo_s.png" alt="LwM2M logo">
</picture>
</center>

<center>
    <a href="https://platformio.org/" style="font-size:2em;vertical-align:middle;"><img src="assets/platformio-logo.png" style="vertical-align: bottom;"> PlatformIO</a>
    <div class="brand-espresiff brands"> </div>
    <div class="brand-arduino brands"> </div>
</center>

import net from 'net';

async function tcpEchoClient(message: string): Promise<void> {
    const client = new net.Socket();

    client.connect(9090, '192.168.1.43', () => {
        console.log('Connected');
        console.log(`Send: ${message}`);
        client.write(message);
    });

    client.on('data', (data) => {
        console.log(`Received: ${data.toString()}`);
        client.end(); // Close the connection once data is received
    });

    client.on('close', () => {
        console.log('Connection closed');
    });

    client.on('error', (err) => {
        console.error('Error:', err.message);
    });
}

const message = 'hello from PC';
tcpEchoClient(message).catch((err) => {
    console.error('Error in TCP client:', err);
});

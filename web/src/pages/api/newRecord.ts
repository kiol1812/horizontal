import type { NextApiRequest, NextApiResponse } from "next";

import { useRouter } from "next/router";

import { getClient } from "@/prismaClient/getClient";
import { record } from "@/types/enumTypes";
const prisma = getClient();

export default async (req: NextApiRequest, res: NextApiResponse) => {
    if(req.method !== 'POST'){
        return res.status(405).json({message:"Methon not allowed."});
    }
    // const userData = JSON.parse(req.body);
    // console.log(req.body); //type/text
    const data:string = req.body;
    const splited = data.split(',');
    const Record:record = {
        time: (await prisma.object.findMany()).length+1,
        offset_x: Number(splited[0].split(':')[1]),
        offset_y: Number(splited[1].split(':')[1].replace('\r\n', ''))
    }
    const savedRecords = await prisma.object.create({
        data: Record
    })

    // const router = useRouter();
    // router.replace("/"); //更新server side props

    res.json(savedRecords);
}